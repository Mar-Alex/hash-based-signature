#include "MerkleTree.h"


MerkleTree::MerkleTree(CryptoPP::HashTransformation *hasher, int size, const CryptoPP::Integer &root) {
	checkSize(size);
	this->hasher = hasher;
	height = getLog2(size) + 1;
	numberOfLeaves = size;
	this->root = root;
}

MerkleTree::MerkleTree(CryptoPP::HashTransformation *hasher, const std::vector<CryptoPP::Integer>& leaves) {

	checkSize(leaves.size());
	this->hasher = hasher;
	height = getLog2(leaves.size()) + 1;
	numberOfLeaves = leaves.size();

	int *leavesOnLayer = new int[height - 1];
	for (int i = 0; i < height - 1; i++)
		leavesOnLayer[i] = numberOfLeaves / (1 << i);

	nodes.resize(height - 1);
	nodes[0] = leaves;
	for (int i = 1; i < height - 1; i++)
		nodes[i].resize(leavesOnLayer[i]);

	for (int i = 1; i < height - 1; i++) {
		for (int j = 0; j < leavesOnLayer[i]; j++)
			concatenateAndHash(nodes[i - 1][j * 2], nodes[i - 1][j * 2 + 1], nodes[i][j]);
	}
	concatenateAndHash(nodes[height - 2][0], nodes[height - 2][1], root);
	delete[] leavesOnLayer;
}

MerkleTree::MerkleTree(CryptoPP::HashTransformation *hasher, int size, int keyLen, char *key) {
	checkSize(size);
	this->hasher = hasher;
	height = getLog2(size) + 1;
	numberOfLeaves = size;

	CryptoPP::byte keyHash[64];
	CryptoPP::SHA512 sha;
	sha.Update((CryptoPP::byte*)key, keyLen);
	sha.Final(keyHash);
	CryptoPP::OFB_Mode<CryptoPP::AES>::Encryption prng;
	prng.SetKeyWithIV(keyHash, 32, keyHash + 32, 16);

	int *leavesOnLayer = new int[height - 1];
	for (int i = 0; i < height - 1; i++)
		leavesOnLayer[i] = numberOfLeaves / (1 << i);

	nodes.resize(height - 1);
	for (int i = 0; i < height - 1; i++)
		nodes[i].resize(leavesOnLayer[i]);

	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters("BitLength", (int)hasher->DigestSize() * 8);

	for (int i = 0; i < numberOfLeaves; i++) {
		nodes[0][i].GenerateRandomNoThrow(prng, params);
	}

	for (int i = 1; i < height - 1; i++) {
		for (int j = 0; j < leavesOnLayer[i]; j++)
			concatenateAndHash(nodes[i - 1][j * 2], nodes[i - 1][j * 2 + 1], nodes[i][j]);
	}
	concatenateAndHash(nodes[height - 2][0], nodes[height - 2][1], root);
	delete[] leavesOnLayer;
}

bool MerkleTree::isBelongToTree(int leafNumber, const CryptoPP::Integer &leaf, const std::vector<CryptoPP::Integer> & authPath) {
	if (leafNumber < 0 || leafNumber >= numberOfLeaves)
		throw std::invalid_argument("Leave number must be positive and less than number of leaves");
	if (height - 1 != authPath.size())
		return false;
	CryptoPP::Integer buffer = leaf;
	for (int i = 0; i < height - 1; i++) {
		if (leafNumber % 2)
			concatenateAndHash(authPath[i], buffer, buffer);
		else
			concatenateAndHash(buffer, authPath[i], buffer);
		leafNumber /= 2;
	}
	return root == buffer;
}

int MerkleTree::getLog2(unsigned int n) {
	int result, i = 31;
	for (; i >= 0; i--)
		if (n & (1 << i)) {
			result = i;
			i--;
			break;
		}
	for (; i >= 0; i--)
		if (n & (1 << i)) {
			result = -1;
			break;
		}
	return result;
}

void MerkleTree::checkSize(int size) {
	if (size <= 0)
		throw std::exception("Size must be positive");
	if (getLog2(size) < 0)
		throw std::exception("Size must be a power of 2");
}

void MerkleTree::concatenateAndHash(const CryptoPP::Integer &a, const CryptoPP::Integer &b, CryptoPP::Integer &result) {
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	a.Encode(buffer, hasher->DigestSize());
	hasher->Update(buffer, hasher->DigestSize());
	b.Encode(buffer, hasher->DigestSize());
	hasher->Update(buffer, hasher->DigestSize());
	hasher->Final(buffer);
	result.Decode(buffer, hasher->DigestSize());
	delete[]buffer;
}

std::vector <CryptoPP::Integer> MerkleTree::formAuthentificationPath(int index) const {
	std::vector<CryptoPP::Integer> authPath(height - 1);
	for (int i = 0; i < height - 1; i++) {
		if (index % 2)
			authPath[i] = nodes[i][index - 1];
		else
			authPath[i] = nodes[i][index + 1];
		index /= 2;
	}
	return authPath;
}

std::vector<std::vector<CryptoPP::Integer>> MerkleTree::getNodes() const {
	std::vector<std::vector<CryptoPP::Integer>> nodesCopy(height);
	for (int i = 0; i < height - 1; i++)
		nodesCopy[i] = nodes[i];
	nodesCopy[height - 1].resize(1);
	nodesCopy[height - 1][0] = root;
	return nodesCopy;
}

std::vector<CryptoPP::Integer> MerkleTree::getLeaves() const {
	std::vector<CryptoPP::Integer> leaves(nodes[0]);
	return leaves;
}

CryptoPP::Integer MerkleTree::getLeaf(int index) const {
	if (index < 0 || index >= numberOfLeaves)
		throw std::invalid_argument("Leave number must be positive and less than number of leaves");
	return nodes[0][index];
}