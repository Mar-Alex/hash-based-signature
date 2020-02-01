#pragma once
#include "MerkleTree.h"
#include "WOTS.h"


class WOTS_MerkleTreePrivateKey
{	
public:
	CryptoPP::HashTransformation *hasher;
	MerkleTree *tree = nullptr;
	std::vector<CryptoPP::Integer> keysForExpansion;
	CryptoPP::Integer privateKey;
	int w;
	int N;
	std::vector<WOTS_Key*> WOTS_PrivateKeys;
	std::vector<WOTS_Key*> WOTS_PublicKeys;
	int index;
	WOTS_MerkleTreePrivateKey() = default;
	WOTS_MerkleTreePrivateKey(int w, int treeSize);
	~WOTS_MerkleTreePrivateKey();
};
