#include "UserInterface.h"

int UserInterface::generateKeyPair(CryptoPP::HashTransformation *hasher, char *password, int passwordLen, \
	int N, int w, std::string publicKeyFileName, std::string privateKeyFileName, std::string extPrivateKeyFileName, \
	std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms, bool saveExtKey) {
	WOTS_MerkleTreePrivateKey *privateKey;
	CryptoPP::Integer publicKey;

	CryptoPP::RandomPool rng;
	rng.IncorporateEntropy((CryptoPP::byte*)password, passwordLen);
	CryptoPP::byte buffer[keyByteLength];
	rng.GenerateBlock(buffer, keyByteLength);

	WOTS_MerkleTreeSignaturer::createKeyPair(hasher, w, 256, N, (char*)buffer, keyByteLength, publicKey, privateKey);
	privateKey->privateKey.Decode(buffer, keyByteLength);
	privateKey->index = 0;

	if (writePublicKey(hasher, publicKey, N, w, publicKeyFileName, hashAlgorithms))
		return 1;
	if (writePrivateKey(hasher, *privateKey, password, passwordLen, privateKeyFileName, hashAlgorithms))
		return 2;
	if (saveExtKey)
		if (writePrivateKeyExt(hasher, *privateKey, password, passwordLen, extPrivateKeyFileName, hashAlgorithms))
			return 3;
	return 0;

}

int UserInterface::writePrivateKey(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey &privateKey, char *password, \
	int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ofstream privateKeyFile;
	privateKeyFile.open(privateKeyFileName, std::ios::binary);
	if (!privateKeyFile.is_open())
		return 1;
	privateKeyFile.write((char *)&privateKey.N, sizeof(int));
	privateKeyFile.write((char *)&privateKey.w, sizeof(int));
	int alg = hashToInt(hasher, hashAlgorithms);
	if (alg == -1)
		return 2;
	privateKeyFile.write((char *)&alg, sizeof(int));
	privateKeyFile.write((char *)&privateKey.index, sizeof(int));

	const int randLen = 32;
	CryptoPP::byte keyByte[randLen], passwordHash[randLen], cryptedKey[randLen], hash[randLen];
	privateKey.privateKey.Encode(keyByte, randLen);
	CryptoPP::SHA256 shaHasher;
	shaHasher.Update((CryptoPP::byte*) password, passwordLen);
	shaHasher.Final(passwordHash);
	for (int i = 0; i < randLen; i++)
		cryptedKey[i] = keyByte[i] ^ passwordHash[i];
	shaHasher.Restart();
	shaHasher.Update((CryptoPP::byte*) &privateKey.N, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &privateKey.w, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &alg, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &privateKey.index, sizeof(int));
	shaHasher.Update(keyByte, randLen);
	shaHasher.Final(hash);

	privateKeyFile.write((char*)cryptedKey, randLen);
	privateKeyFile.write((char*)hash, randLen);

	privateKeyFile.close();
	return 0;
}

int UserInterface::readPublicKey(CryptoPP::HashTransformation *&hasher, CryptoPP::Integer &publicKey, int &N, int &w, \
	std::string publicKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ifstream publicKeyFile;
	publicKeyFile.open(publicKeyFileName, std::ios::binary);
	if (!publicKeyFile.is_open()) {
		return 1;
	}
	publicKeyFile.read((char*)&N, sizeof(int));
	publicKeyFile.read((char*)&w, sizeof(int));
	int alg;
	publicKeyFile.read((char*)&alg, sizeof(int));
	if (hashAlgorithms->find(alg) == hashAlgorithms->end())
		return 2;
	hasher = hashAlgorithms->find(alg)->second;
	CryptoPP::byte * buffer = new CryptoPP::byte[hasher->DigestSize()];
	publicKeyFile.read((char*)buffer, hasher->DigestSize());
	publicKey.Decode(buffer, hasher->DigestSize());
	publicKeyFile.close();
	delete[]buffer;
	try {
		MerkleTree::checkSize(N);
	}
	catch (std::exception e) {
		return 3;
	}
	if (w < 1 || w > 16)
		return 4;
	return 0;
}

int UserInterface::readPrivateKey(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey *&privateKey, char *password, \
	int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ifstream privateKeyFile;
	privateKeyFile.open(privateKeyFileName, std::ios::binary);
	if (!privateKeyFile.is_open())
		return 1;
	int N, w, alg, index;
	privateKeyFile.read((char*)&N, sizeof(int));
	privateKeyFile.read((char*)&w, sizeof(int));
	privateKeyFile.read((char*)&alg, sizeof(int));
	if (hashAlgorithms->find(alg) == hashAlgorithms->end())
		return 2;
	privateKeyFile.read((char*)&index, sizeof(int));

	const int randLen = 32;
	CryptoPP::byte keyByte[randLen], passwordHash[randLen], cryptedKey[randLen], hash[randLen], computedHash[randLen];
	privateKeyFile.read((char*)cryptedKey, randLen);
	privateKeyFile.read((char*)hash, randLen);

	CryptoPP::SHA256 shaHasher;
	shaHasher.Update((CryptoPP::byte*) password, passwordLen);
	shaHasher.Final(passwordHash);
	for (int i = 0; i < randLen; i++)
		keyByte[i] = cryptedKey[i] ^ passwordHash[i];
	shaHasher.Restart();
	shaHasher.Update((CryptoPP::byte*) &N, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &w, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &alg, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &index, sizeof(int));
	shaHasher.Update(keyByte, randLen);
	shaHasher.Final(computedHash);
	for (int i = 0; i < randLen; i++)
		if (hash[i] != computedHash[i])
			return 3;

	hasher = hashAlgorithms->find(alg)->second;
	CryptoPP::Integer publicKey;
	WOTS_MerkleTreeSignaturer::createKeyPair(hasher, w, 256, N, (char*)keyByte, keyByteLength, publicKey, privateKey);
	privateKey->index = index;
	privateKey->N = N;
	privateKey->w = w;
	return 0;
}

int UserInterface::readSignature(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreeSignature &signature, \
	std::string filename, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ifstream fin;
	fin.open(filename, std::ios::binary);
	if (!fin.is_open())
		return 1;
	fin.read((char*)&signature.treeSize, sizeof(int));
	fin.read((char*)&signature.w, sizeof(int));
	int alg;
	fin.read((char*)&alg, sizeof(int));
	if (hashAlgorithms->find(alg) == hashAlgorithms->end())
		return 2;
	hasher = hashAlgorithms->find(alg)->second;
	fin.read((char*)&signature.index, sizeof(int));
	int size;
	fin.read((char*)&size, sizeof(int));

	signature.WOTS.resize(size);
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	for (int i = 0; i < signature.WOTS.size(); i++) {
		fin.read((char*)buffer, hasher->DigestSize());
		signature.WOTS[i].Decode(buffer, hasher->DigestSize());
	}

	fin.read((char*)&size, sizeof(int));
	signature.authPath.resize(size);
	for (int i = 0; i < signature.authPath.size(); i++) {
		fin.read((char*)buffer, hasher->DigestSize());
		signature.authPath[i].Decode(buffer, hasher->DigestSize());
	}
	fin.close();
	delete[]buffer;
	try {
		MerkleTree::checkSize(signature.treeSize);
	}
	catch (std::exception e) {
		return 3;
	}
	if (signature.w < 1 || signature.w > 16)
		return 4;
	return 0;
}

int UserInterface::writeSignature(CryptoPP::HashTransformation *hasher, WOTS_MerkleTreeSignature &signature, \
	std::string filename, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ofstream fout;
	fout.open(filename, std::ios::binary);
	if (!fout.is_open())
		return 1;
	fout.write((char*)&signature.treeSize, sizeof(int));
	fout.write((char*)&signature.w, sizeof(int));
	int alg = hashToInt(hasher, hashAlgorithms);
	if (alg == -1)
		return 2;
	fout.write((char *)&alg, sizeof(int));
	fout.write((char*)&signature.index, sizeof(int));
	int size = signature.WOTS.size();
	fout.write((char*)&size, sizeof(int));
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	for (int i = 0; i < signature.WOTS.size(); i++) {
		signature.WOTS[i].Encode(buffer, hasher->DigestSize());
		fout.write((char*)buffer, hasher->DigestSize());
	}
	size = signature.authPath.size();
	fout.write((char*)&size, sizeof(int));
	for (int i = 0; i < signature.authPath.size(); i++) {
		signature.authPath[i].Encode(buffer, hasher->DigestSize());
		fout.write((char*)buffer, hasher->DigestSize());
	}
	fout.close();
	delete[] buffer;
	return fout.is_open();
}

int UserInterface::verifySignature(std::string filename, std::string signatureFilename, std::string keyFilename, \
	std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	CryptoPP::HashTransformation *keyHasher, *signHasher;
	int keyN, signN, keyW, signW;
	CryptoPP::Integer publicKey;
	if (readPublicKey(keyHasher, publicKey, keyN, keyW, keyFilename, hashAlgorithms))
		return 1;
	WOTS_MerkleTreeSignature signature;
	try {
		if (readSignature(signHasher, signature, signatureFilename, hashAlgorithms))
			return 2;
	}
	catch (std::exception e) {
		return 3;
	}
	if (keyHasher != signHasher || keyN != signature.treeSize || keyW != signature.w ||
		signature.index >= signature.treeSize)
		return 4;

	bool isSignatureCorrect = WOTS_MerkleTreeSignaturer::verifySignatureFile(keyHasher, filename, publicKey, signature);
	return !isSignatureCorrect;
}

int UserInterface::createSignature(std::string filename, std::string signatureFilename, std::string keyFilename, std::string password, \
	CryptoPP::HashTransformation *hasher, WOTS_MerkleTreePrivateKey *privateKey, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms, bool isKeyFull) {
	WOTS_MerkleTreeSignature signature;
	if (!isKeyFull) {
		CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
		privateKey->keysForExpansion[privateKey->index].Encode(buffer, hasher->DigestSize());
		WOTS::createKeyPair(hasher, privateKey->w, 256, buffer, hasher->DigestSize(), privateKey->WOTS_PublicKeys[privateKey->index], privateKey->WOTS_PrivateKeys[privateKey->index]);
	}
	int result = WOTS_MerkleTreeSignaturer::createSignatureFile(hasher, filename, *privateKey, signature, privateKey->index);
	if (result)
		return 1;
	writeSignature(hasher, signature, signatureFilename, hashAlgorithms);
	privateKey->index++;
	return 0;
}

int UserInterface::writePublicKey(CryptoPP::HashTransformation *hasher, CryptoPP::Integer &key, int N, int w, \
	std::string publicKeyFilename, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ofstream publicKeyFile;
	publicKeyFile.open(publicKeyFilename, std::ios::binary);
	if (!publicKeyFile.is_open())
		return 1;
	publicKeyFile.write((char*)&N, sizeof(int));
	publicKeyFile.write((char*)&w, sizeof(int));
	int alg = hashToInt(hasher, hashAlgorithms);
	if (alg == -1)
		return 2;
	publicKeyFile.write((char*)&alg, sizeof(int));
	CryptoPP::byte *keyByte = new CryptoPP::byte[hasher->DigestSize()];
	key.Encode(keyByte, hasher->DigestSize());
	publicKeyFile.write((char*)keyByte, hasher->DigestSize());
	publicKeyFile.close();
	delete[]keyByte;
	return 0;
}

int UserInterface::writePrivateKeyExt(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey &privateKey, char *password, \
	int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ofstream privateKeyFile;
	privateKeyFile.open(privateKeyFileName, std::ios::binary);
	if (!privateKeyFile.is_open())
		return 1;
	privateKeyFile.write((char *)&privateKey.N, sizeof(int));
	privateKeyFile.write((char *)&privateKey.w, sizeof(int));
	int alg = hashToInt(hasher, hashAlgorithms);
	if (alg == -1)
		return 2;
	privateKeyFile.write((char *)&alg, sizeof(int));
	privateKeyFile.write((char *)&privateKey.index, sizeof(int));
	CryptoPP::byte keyBuffer[keyByteLength], passwordHash[keyByteLength];
	CryptoPP::SHA256 shaHasher;
	shaHasher.Update((CryptoPP::byte*) password, passwordLen);
	shaHasher.Final(passwordHash);
	shaHasher.Restart();
	shaHasher.Update((CryptoPP::byte*) &privateKey.N, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &privateKey.w, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &alg, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &privateKey.index, sizeof(int));

	CryptoPP::byte *cipherBuffer = new CryptoPP::byte[keyByteLength + privateKey.N * hasher->DigestSize()];
	CryptoPP::byte *treeNodeBuffer = new CryptoPP::byte[hasher->DigestSize()];
	privateKey.privateKey.Encode(keyBuffer, keyByteLength);
	shaHasher.Update(keyBuffer, keyByteLength);
	memcpy(cipherBuffer, keyBuffer, keyByteLength);

	std::vector<CryptoPP::Integer> leaves = privateKey.tree->getLeaves();
	for (int i = 0; i < privateKey.N; i++) {
		leaves[i].Encode(treeNodeBuffer, hasher->DigestSize());
		memcpy(cipherBuffer + keyByteLength + i * hasher->DigestSize(), treeNodeBuffer, hasher->DigestSize());
		shaHasher.Update(treeNodeBuffer, hasher->DigestSize());
	}
	shaHasher.Final(keyBuffer);

	CryptoPP::byte IV[] = "0123456789ABCDEF";
	CryptoPP::SecByteBlock iv(IV, CryptoPP::AES::BLOCKSIZE);
	CryptoPP::CFB_Mode<CryptoPP::AES>::Encryption cfbEncryption(passwordHash, keyByteLength, IV);
	cfbEncryption.ProcessData(cipherBuffer, cipherBuffer, keyByteLength + privateKey.N * hasher->DigestSize());
	
	privateKeyFile.write((char *)cipherBuffer, keyByteLength + privateKey.N * hasher->DigestSize());
	privateKeyFile.write((char *)keyBuffer, keyByteLength);
	privateKeyFile.close();
	delete[] treeNodeBuffer;
	delete[] cipherBuffer;
	return 0;
}

int UserInterface::readPrivateKeyExt(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey *&privateKey, char *password, \
	int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	std::ifstream privateKeyFile;
	privateKeyFile.open(privateKeyFileName, std::ios::binary);
	if (!privateKeyFile.is_open())
		return 1;
	int N, w, alg, index;
	privateKeyFile.read((char*)&N, sizeof(int));
	privateKeyFile.read((char*)&w, sizeof(int));
	privateKeyFile.read((char*)&alg, sizeof(int));
	if (hashAlgorithms->find(alg) == hashAlgorithms->end())
		return 2;
	privateKeyFile.read((char*)&index, sizeof(int));
	try {
		MerkleTree::checkSize(N);
	}
	catch (std::exception e) {
		return 3;
	}
	hasher = hashAlgorithms->find(alg)->second;
	CryptoPP::byte *cipherBuffer = new CryptoPP::byte[keyByteLength + N * hasher->DigestSize()];
	std::vector<CryptoPP::Integer> leaves(N);
	privateKeyFile.read((char*)cipherBuffer, keyByteLength + N * hasher->DigestSize());
	CryptoPP::byte keyByte[keyByteLength], passwordHash[keyByteLength], resultHash[keyByteLength], resultHashComputed[keyByteLength];
	CryptoPP::SHA256 shaHasher;
	shaHasher.Update((CryptoPP::byte*) password, passwordLen);
	shaHasher.Final(passwordHash);

	CryptoPP::byte IV[] = "0123456789ABCDEF";
	CryptoPP::SecByteBlock iv(IV, CryptoPP::AES::BLOCKSIZE);
	CryptoPP::CFB_Mode<CryptoPP::AES>::Decryption cfbDecryption(passwordHash, keyByteLength, iv);
	cfbDecryption.ProcessData(cipherBuffer, cipherBuffer, keyByteLength + N * hasher->DigestSize());


	privateKeyFile.read((char*)resultHash, keyByteLength);

	shaHasher.Update((CryptoPP::byte*) &N, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &w, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &alg, sizeof(int));
	shaHasher.Update((CryptoPP::byte*) &index, sizeof(int));
	shaHasher.Update(cipherBuffer, keyByteLength + N * hasher->DigestSize());
	shaHasher.Final(resultHashComputed);
	if (memcmp(resultHash, resultHashComputed, keyByteLength))
		return 4;
	memcpy(keyByte, cipherBuffer, keyByteLength);

	privateKey = new WOTS_MerkleTreePrivateKey(w, N);
	CryptoPP::byte keyHash[64];
	CryptoPP::SHA512 sha;
	sha.Update((CryptoPP::byte*)keyByte, keyByteLength);
	sha.Final(keyHash);
	CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption prng;
	prng.SetKeyWithIV(keyHash, 32, keyHash + 32, 16);
	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters("BitLength", (int)hasher->DigestSize() * 8);

	std::vector<CryptoPP::Integer> keyHashes(N);
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];

	for (int i = 0; i < N; i++) {
		privateKey->keysForExpansion[i].GenerateRandom(prng, params);
		memcpy(buffer, cipherBuffer + keyByteLength + i * hasher->DigestSize(), hasher->DigestSize());
		keyHashes[i].Decode(buffer, hasher->DigestSize());
	}
	privateKey->tree = new MerkleTree(hasher, keyHashes);
	privateKey->index = index;
	privateKey->hasher = hasher;
	delete[]cipherBuffer;
	delete[]buffer;
	return 0;
}

int UserInterface::hashToInt(CryptoPP::HashTransformation *hasher, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms) {
	for (std::pair<int, CryptoPP::HashTransformation*> element : *hashAlgorithms)
		if (element.second == hasher)
			return element.first;
	return -1;
}

bool UserInterface::checkFilename(std::string filename, bool read) {
	if (read) {
		std::ifstream file;
		file.open(filename);
		if (file.is_open()) {
			file.close();
			return false;
		}
		return true;
	}
	std::ofstream file;
	file.open(filename);
	if (file.is_open()) {
		file.close();
		return false;
	}
	return true;
}