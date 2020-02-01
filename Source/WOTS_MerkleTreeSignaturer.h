#pragma once

#include "WOTS_Key.h"
#include "WOTS_MerkleTreePrivateKey.h"
#include "Hash.h"

struct WOTS_MerkleTreeSignature {
	std::vector <CryptoPP::Integer> WOTS;
	int index;
	std::vector <CryptoPP::Integer> authPath;
	int w;
	int treeSize;
};


class WOTS_MerkleTreeSignaturer {

	static bool verifySignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash, const CryptoPP::Integer &publicKey, WOTS_MerkleTreeSignature &signature);

public:

	static void createKeyPair(CryptoPP::HashTransformation *hasher, int w, int m, int treeSize, char *key, int keyLen, CryptoPP::Integer &publicKey, WOTS_MerkleTreePrivateKey *&privateKey);

	static void createSignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, const WOTS_MerkleTreePrivateKey &privateKey, WOTS_MerkleTreeSignature &signature, int index);
	static bool verifySignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, CryptoPP::Integer publicKey, WOTS_MerkleTreeSignature &signature);

	static int createSignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, const WOTS_MerkleTreePrivateKey &privateKey, WOTS_MerkleTreeSignature &signature, int index);
	static bool verifySignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, CryptoPP::Integer publicKey, WOTS_MerkleTreeSignature &signature);
};

