#pragma once

#include <vector>
#include "cryptopp/integer.h"
#include "cryptopp/iterhash.h"
#include "cryptopp/randpool.h"
#include "cryptopp/algparam.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/sha.h"

class MerkleTree
{
	int numberOfLeaves;
	int height;
	std::vector<std::vector<CryptoPP::Integer>> nodes;
	CryptoPP::HashTransformation *hasher;
	CryptoPP::Integer root;

	static int getLog2(unsigned int n);

	void concatenateAndHash(const CryptoPP::Integer &a, const CryptoPP::Integer &b, CryptoPP::Integer &result);
public:
	static void checkSize(int size);
	MerkleTree(CryptoPP::HashTransformation *hasher, int size, const CryptoPP::Integer &root);
	MerkleTree(CryptoPP::HashTransformation *hasher, const std::vector<CryptoPP::Integer>& leaves);
	MerkleTree(CryptoPP::HashTransformation *hasher, int size, int keyLen, char *key);
	~MerkleTree() = default;

	bool isBelongToTree(int leaveNumber, const CryptoPP::Integer &leave, const std::vector<CryptoPP::Integer> & authPath);
	CryptoPP::Integer getRoot() const { return root; }
	int getNumberOfLeaves() const { return numberOfLeaves; }
	int getHeight() const { return height; }
	std::vector<CryptoPP::Integer> getLeaves() const;
	std::vector<std::vector<CryptoPP::Integer>> getNodes() const;
	std::vector<CryptoPP::Integer> formAuthentificationPath(int index) const;
	CryptoPP::Integer getLeaf(int index) const;
};