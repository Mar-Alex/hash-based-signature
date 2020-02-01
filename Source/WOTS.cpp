#include "WOTS.h"


void WOTS::createSignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature) {
	signature.resize(privateKey.t);
	int checkSum = 0;
	int i = 0;
	for (; i < privateKey.t1; i++) {
		int signaturedBitString = hash.GetBits(i * privateKey.w, privateKey.w);
		checkSum += privateKey.numberOfIterations - signaturedBitString;
		Hash::cyclicHashing(hasher, privateKey.key[i], signaturedBitString, signature[i]);
	}
	CryptoPP::Integer bigCheckSum = checkSum;
	for (int j = 0; j < privateKey.t2; j++) {
		int signaturedBitString = bigCheckSum.GetBits(j * privateKey.w, privateKey.w);
		Hash::cyclicHashing(hasher, privateKey.key[i + j], signaturedBitString, signature[i + j]);
	}
}

bool WOTS::verifySignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature) {
	if (signature.size() != publicKey.t)
		throw std::invalid_argument("Array size must be equal t");
	std::vector<CryptoPP::Integer> hashedSignature(publicKey.t);
	int checkSum = 0;
	int i = 0;
	for (; i < publicKey.t1; i++) {
		int signaturedBitString = hash.GetBits(i * publicKey.w, publicKey.w);
		checkSum += publicKey.numberOfIterations - signaturedBitString;
		Hash::cyclicHashing(hasher, signature[i], publicKey.numberOfIterations - signaturedBitString, hashedSignature[i]);
		if (publicKey.key[i] != hashedSignature[i])
			return false;
	}
	CryptoPP::Integer bigCheckSum = checkSum;
	for (int j = 0; j < publicKey.t2; j++) {
		int signaturedBitString = bigCheckSum.GetBits(j * publicKey.w, publicKey.w);
		Hash::cyclicHashing(hasher, signature[i + j], publicKey.numberOfIterations - signaturedBitString, hashedSignature[i + j]);
		if (publicKey.key[i + j] != hashedSignature[i + j])
			return false;
	}
	return true;
}

void WOTS::createKeyPair(CryptoPP::HashTransformation *hasher, int w, int m, CryptoPP::byte *key, int keyLen, WOTS_Key *&publicKey, WOTS_Key *&privateKey) {
	publicKey = new WOTS_Key(w, m);
	privateKey = new WOTS_Key(w, m);
	CryptoPP::byte keyHash[64];
	CryptoPP::SHA512 sha;
	sha.Update((CryptoPP::byte*)key, keyLen);
	sha.Final(keyHash);
	CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption prng;
	prng.SetKeyWithIV(keyHash, 32, keyHash + 32, 16);
	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters("BitLength", (int)hasher->DigestSize() * 8);
	for (int i = 0; i < privateKey->t; i++) {
		privateKey->key[i].GenerateRandom(prng, params);
		Hash::cyclicHashing(hasher, privateKey->key[i], privateKey->numberOfIterations, publicKey->key[i]);
	}
}

void WOTS::createSignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature) {
	CryptoPP::SHA256 hashSHA256;
	CryptoPP::Integer hash;
	Hash::formHashString(&hashSHA256, (CryptoPP::byte*)message, length, hash);
	createSignature(hasher, hash, privateKey, signature);
}

int WOTS::createSignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature) {
	CryptoPP::SHA256 hashSHA256;
	CryptoPP::Integer hash;
	int result = Hash::formHashFile(&hashSHA256, filename, hash);
	if (result)
		return 1;
	createSignature(hasher, hash, privateKey, signature);
	return 0;
}

bool WOTS::verifySignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature) {
	CryptoPP::SHA256 hashSHA256;
	CryptoPP::Integer hash;
	Hash::formHashString(hasher, (CryptoPP::byte*)message, length, hash);
	bool result = verifySignature(hasher, hash, publicKey, signature);
	return result;
}

bool WOTS::verifySignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature) {
	CryptoPP::SHA256 hashSHA256;
	CryptoPP::Integer hash;
	Hash::formHashFile(hasher, filename, hash);
	bool result = verifySignature(hasher, hash, publicKey, signature);
	return result;
}
