#include "Hash.h"

int Hash::formHashFile(CryptoPP::HashTransformation *hasher, std::string filename, CryptoPP::Integer &result) {
	int byte_len = 64;
	FILE *file;
	fopen_s(&file, filename.c_str(), "rb");
	if (!file)
		return 1;
	int a;
	char *str = new char[byte_len];
	while (!feof(file))
	{
		a = fread(str, 1, byte_len, file);
		hasher->Update((CryptoPP::byte*)str, a);
	}

	CryptoPP::byte* buffer = new CryptoPP::byte[hasher->DigestSize()];
	hasher->Final(buffer);
	result.Decode(buffer, hasher->DigestSize());
	delete[] str;
	delete[] buffer;
	return fclose(file);
}

void Hash::cyclicHashing(CryptoPP::HashTransformation *hasher, const CryptoPP::Integer &a, int numberOfIterations, CryptoPP::Integer &result) {
	if (numberOfIterations < 0)
		throw std::invalid_argument("Nu,ber of iterations must be positive");
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	a.Encode(buffer, hasher->DigestSize());
	for (int i = 0; i < numberOfIterations; i++) {
		hasher->Update(buffer, hasher->DigestSize());
		hasher->Final(buffer);
	}
	result.Decode(buffer, hasher->DigestSize());
	delete[] buffer;
}

void Hash::formHashForArray(CryptoPP::HashTransformation *hasher, const std::vector<CryptoPP::Integer> &arr, CryptoPP::Integer &result) {
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	for (int i = 0; i < arr.size(); i++) {
		arr[i].Encode(buffer, hasher->DigestSize());
		hasher->Update(buffer, hasher->DigestSize());
	}
	hasher->Final(buffer);
	result.Decode(buffer, hasher->DigestSize());
	delete[] buffer;
}

void Hash::formHashString(CryptoPP::HashTransformation *hasher, const CryptoPP::byte *message, int len, CryptoPP::Integer &result) {
	CryptoPP::byte *buffer = new CryptoPP::byte[hasher->DigestSize()];
	hasher->Update(message, len);
	hasher->Final(buffer);
	result.Decode(buffer, hasher->DigestSize());
	delete[]buffer;
}
