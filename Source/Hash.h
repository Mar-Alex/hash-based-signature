#pragma once

#include <string>
#include <vector>
#include <fstream>
#include "cryptopp/integer.h"

class Hash
{
public:
	static void formHashForArray(CryptoPP::HashTransformation *hasher, const std::vector<CryptoPP::Integer> &arr, CryptoPP::Integer &result);
	static int formHashFile(CryptoPP::HashTransformation *hasher, std::string filename, CryptoPP::Integer &result);
	static void cyclicHashing(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &a, int numberOfIterations, CryptoPP::Integer &result);
	static void formHashString(CryptoPP::HashTransformation *hasher, const CryptoPP::byte *message, int len, CryptoPP::Integer &result);
};