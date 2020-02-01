#pragma once
#include <map>
#include <iostream>
#include "cryptopp/cryptlib.h"
#include "cryptopp/sha.h"
#include "cryptopp/sha3.h"
#include "cryptopp/blake2.h"
#include "cryptopp/shake.h"
#include "cryptopp/tiger.h"
#include "cryptopp/ripemd.h"
#include "cryptopp/whrlpool.h"
#include "cryptopp/sm3.h"
#include "cryptopp/md5.h"

class HashAlgorithmGenerator
{	
public:
	static std::map<int, CryptoPP::HashTransformation*> *getHashes() {
		std::map<int, CryptoPP::HashTransformation*> *result = new std::map<int, CryptoPP::HashTransformation*>;
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(0, new CryptoPP::SHA1));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(1, new CryptoPP::SHA256));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(2, new CryptoPP::SHA512));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(3, new CryptoPP::SHA3_256));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(4, new CryptoPP::SHA3_512));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(5, new CryptoPP::BLAKE2b));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(6, new CryptoPP::SHAKE256));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(7, new CryptoPP::Tiger));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(8, new CryptoPP::RIPEMD128));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(9, new CryptoPP::RIPEMD256));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(10, new CryptoPP::Whirlpool));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(11, new CryptoPP::SM3));
		result->insert(std::pair<int, CryptoPP::HashTransformation*>(12, new CryptoPP::MD5));
		return result;
	}
};

