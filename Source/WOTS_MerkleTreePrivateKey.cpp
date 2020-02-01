#include "WOTS_MerkleTreePrivateKey.h"


WOTS_MerkleTreePrivateKey::WOTS_MerkleTreePrivateKey(int w, int treeSize) {
	this->N = treeSize;
	this->w = w;
	WOTS_PrivateKeys.resize(treeSize);
	WOTS_PublicKeys.resize(treeSize);
	keysForExpansion.resize(treeSize);
}

WOTS_MerkleTreePrivateKey::~WOTS_MerkleTreePrivateKey() {
	for (WOTS_Key*a : WOTS_PrivateKeys)
		if (a)
			delete a;
	for (WOTS_Key*a : WOTS_PublicKeys)
		if (a)
			delete a;
	if (tree)
		delete tree;
}