#pragma once

#include <iostream>
#include <conio.h>
#include <time.h>
#include <vector>
#include <string>
#include <fstream>

#include "WOTS.h"
#include "MerkleTree.h"
#include "WOTS_MerkleTreeSignaturer.h"


class UserInterface
{
private:
	const static int keyByteLength = 32;

	static int writeSignature(CryptoPP::HashTransformation *hasher, WOTS_MerkleTreeSignature &signature, std::string filename, \
		std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int readSignature(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreeSignature &signature, std::string filename, \
		std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int writePublicKey(CryptoPP::HashTransformation *hasher, CryptoPP::Integer &key, int N, int w, \
		std::string publicKeyFileNam, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int hashToInt(CryptoPP::HashTransformation *hasher, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);
public:

	static int generateKeyPair(CryptoPP::HashTransformation *hasher, char *password, int passwordLen,\
		int treeSize, int w, std::string publicKeyFileName, std::string privateKeyFileName, std::string extPrivateKeyFileName, \
		std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms, bool saveExtKey);

	static int readPublicKey(CryptoPP::HashTransformation *&hasher, CryptoPP::Integer & publicKey, int &N, int &w,\
		std::string publicKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int readPrivateKey(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey *&privateKey, char *password, \
		int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int verifySignature(std::string filename, std::string signatureFilename, std::string keyFilename,\
		std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int createSignature(std::string filename, std::string signatureFilename, std::string keyFilename, std::string password, \
		CryptoPP::HashTransformation *hasher, WOTS_MerkleTreePrivateKey *privateKey, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms, bool isKeyFull);

	static int writePrivateKey(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey &privateKey, char *password, \
		int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int writePrivateKeyExt(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey &privateKey, char *password, \
		int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static int readPrivateKeyExt(CryptoPP::HashTransformation *&hasher, WOTS_MerkleTreePrivateKey *&privateKey, char *password, \
		int passwordLen, std::string privateKeyFileName, std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms);

	static bool checkFilename(std::string filename, bool read);
};