#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <bitset>

using namespace std;

std::string toBinary(int n)
{
	std::string r;
	while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
	return r;
}
void stringToBinary(string myString) {
	for (std::size_t i = 0; i < myString.size(); ++i)
	{
		cout << bitset<8>(myString.c_str()[i]) << endl;
	}
}

void compute_md5(char* str, unsigned char digest[16]) {
	MD5_CTX ctx;
	MD5_Init(&ctx);	
	MD5_Update(&ctx, str, strlen(str));
	MD5_Final(digest, &ctx);
}

void sha256(char* str, unsigned char digest[32])
{
	//unsigned char hash[32];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str, 16);
	SHA256_Final(digest, &sha256);
}
int main() {

	FILE* fp = fopen("wordlist.txt", "rb");
	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);
	}

	char chunk[128];
	long long newSalt = 0;
	while (fgets(chunk, sizeof(chunk), fp)) {
		cout << chunk;
		cout << toBinary(newSalt) << endl;
		cout <<"valoare ASCII este: " << int(chunk) << endl;
		cout << newSalt << endl;
		newSalt++;
		//chunk[strcspn(chunk, "\r\n")] = 0;

		//string chunkString = string(chunk);
		//cout << chunkString << endl;
		//string newChunk = chunkString+to_string(newSalt);
		//cout << newChunk<< endl;

		//char* cstr = new char[newChunk.length() + 1];
		//strcpy(cstr, newChunk.c_str());

		//unsigned char digest[16];
		//sha256(cstr, digest);

		//stringstream ss;
		//for (int i = 0; i < 32; i++)
		//{
		//	ss << hex << setw(2) << setfill('0') << (int)digest[i];
		//}
		//string sha256Result = ss.str();
		//cout << sha256Result;
		//delete[] cstr;
		//cout << i << endl;
	}
	fclose(fp);
	return 0;
	};
