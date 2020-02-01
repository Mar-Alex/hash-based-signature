#pragma once

#include <vector>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/sha.h"
#include "Hash.h"
#include "WOTS_Key.h"


class WOTS
{
	static void createSignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature);
	static bool verifySignature(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &hash, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature);

public:

	static void createKeyPair(CryptoPP::HashTransformation *hasher, int w, int m, CryptoPP::byte *key, int keyLen, WOTS_Key *&publicKey, WOTS_Key *&privateKey);

	static void createSignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature);
	static int createSignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, const WOTS_Key &privateKey, std::vector<CryptoPP::Integer> &signature);

	static bool verifySignatureString(CryptoPP::HashTransformation *hasher, char * message, int length, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature);
	static bool verifySignatureFile(CryptoPP::HashTransformation *hasher, std::string filename, const WOTS_Key &publicKey, std::vector<CryptoPP::Integer> &signature);
};