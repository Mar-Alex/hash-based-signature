#pragma once

#include <vector>
#include "cryptopp/integer.h"

struct WOTS_Key
{
public:
	int w;
	int numberOfIterations;
	int t, t1, t2;
	std::vector<CryptoPP::Integer> key;

	WOTS_Key(int w, int m);
	~WOTS_Key() = default;
};

