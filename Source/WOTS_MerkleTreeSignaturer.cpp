#include "WOTS_MerkleTreeSignaturer.h"

bool WOTS_MerkleTreeSignaturer::verifySignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash,\
	const CryptoPP::Integer &publicKey, WOTS_MerkleTreeSignature &signature) {
	CryptoPP::Integer root;
	std::vector < CryptoPP::Integer> hashedSignature(signature.WOTS.size());
	int checkSum = 0;
	int i = 0;
	int numberOfIterations = (1 << signature.w) - 1;
	double mw = (double)256 / signature.w;
	int t1 = (mw > (int)mw) ? mw + 1 : mw;
	int t2 = log2(t1 * numberOfIterations) / signature.w + 1;
	if (t1 + t2 != signature.WOTS.size())
		return false;

	for (; i < t1; i++) {
		int signaturedBitString = hash.GetBits(i * signature.w, signature.w);
		checkSum += numberOfIterations - signaturedBitString;
		Hash::cyclicHashing(hasher, signature.WOTS[i], numberOfIterations - signaturedBitString, hashedSignature[i]);
	}
	CryptoPP::Integer bigCheckSum = checkSum;
	for (int j = 0; j < t2; j++) {
		int signaturedBitString = bigCheckSum.GetBits(j * signature.w, signature.w);
		Hash::cyclicHashing(hasher, signature.WOTS[i + j], numberOfIterations - signaturedBitString, hashedSignature[i + j]);
	}
	CryptoPP::Integer hashedWOTSKey;
	Hash::formHashForArray(hasher, hashedSignature, hashedWOTSKey);
	MerkleTree tree(hasher, signature.treeSize, publicKey);
	bool result = tree.isBelongToTree(signature.index, hashedWOTSKey, signature.authPath);
	return result;
}


void WOTS_MerkleTreeSignaturer::createKeyPair(CryptoPP::HashTransformation *hasher, int w, int m, int treeSize,\
	char *key, int keyLen, CryptoPP::Integer &publicKey, WOTS_MerkleTreePrivateKey *&privateKey) {
	MerkleTree::checkSize(treeSize);
	privateKey = new WOTS_MerkleTreePrivateKey(w, treeSize);

	CryptoPP::byte keyHash[64];
	CryptoPP::SHA512 sha;
	sha.Update((CryptoPP::byte*)key, keyLen);
	sha.Final(keyHash);
	CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption prng;
	prng.SetKeyWithIV(keyHash, 32, keyHash + 32, 16);
	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters("BitLength", (int)hasher->DigestSize() * 8);

	std::vector<CryptoPP::Integer> keyHashes(treeSize);
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];

	for (int i = 0; i < treeSize; i++) {
		privateKey->keysForExpansion[i].GenerateRandom(prng, params);
		privateKey->keysForExpansion[i].Encode(buffer, hasher->DigestSize());
		WOTS::createKeyPair(hasher, w, m, buffer, hasher->DigestSize(), privateKey->WOTS_PublicKeys[i], privateKey->WOTS_PrivateKeys[i]);
		Hash::formHashForArray(hasher, privateKey->WOTS_PublicKeys[i]->key, keyHashes[i]);
	}
	privateKey->tree = new MerkleTree(hasher, keyHashes);
	publicKey = privateKey->tree->getRoot();
}


void WOTS_MerkleTreeSignaturer::createSignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, \
	const WOTS_MerkleTreePrivateKey &privateKey, WOTS_MerkleTreeSignature &signature, int index) {
	WOTS::createSignatureString(hasher, message, length, *privateKey.WOTS_PrivateKeys[index], signature.WOTS);
	signature.index = index;
	signature.authPath = privateKey.tree->formAuthentificationPath(index);
	signature.w = privateKey.w;
	signature.treeSize = privateKey.tree->getNumberOfLeaves();
}


bool WOTS_MerkleTreeSignaturer::verifySignatureString(CryptoPP::HashTransformation *hasher, char * message, int length,\
	CryptoPP::Integer publicKey, WOTS_MerkleTreeSignature &signature) {
	CryptoPP::SHA256 hasherSHA256;
	CryptoPP::Integer hash;
	Hash::formHashString(&hasherSHA256, (CryptoPP::byte*)message, length, hash);
	bool result = verifySignature(hasher, hash, publicKey, signature);
	return result;
}


int WOTS_MerkleTreeSignaturer::createSignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, \
	const WOTS_MerkleTreePrivateKey &privateKey, WOTS_MerkleTreeSignature &signature, int index) {
	int result = WOTS::createSignatureFile(hasher, filename, *privateKey.WOTS_PrivateKeys[index], signature.WOTS);
	signature.index = index;
	signature.authPath = privateKey.tree->formAuthentificationPath(index);
	signature.w = privateKey.w;
	signature.treeSize = privateKey.tree->getNumberOfLeaves();
	return result;
}


bool WOTS_MerkleTreeSignaturer::verifySignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, CryptoPP::Integer publicKey, WOTS_MerkleTreeSignature &signature) {
	CryptoPP::SHA256 hasherSHA256;
	CryptoPP::Integer hash;
	Hash::formHashFile(&hasherSHA256, filename, hash);
	bool result = verifySignature(hasher, hash, publicKey, signature);
	return result;
}