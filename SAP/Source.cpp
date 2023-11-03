
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

using namespace std;

void compute_sha256(char* str, unsigned char digest[32]) {
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str, strlen(str));
	SHA256_Final(digest, &sha256);
}

void sha256(unsigned char str[16], unsigned char digest[32])
{
	//unsigned char hash[32];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, str, 16);
	SHA256_Final(digest, &sha256);
	/*stringstream ss;
	for (int i = 0; i < 32; i++)
	{
		ss << hex << setw(2) << setfill('0') << (int)hash[i];
	}
	return ss.str();*/
}
int main() {
	string str;
	int i = 0;


	FILE* fp = fopen("wordlist.txt", "rb");
	if (fp == NULL) {
		perror("Unable to open file!");
		exit(1);
	}
	FILE* destinationFile = NULL;
	fopen_s(&destinationFile, "destination.txt", "wb");

	char chunk[256];
	//string salt = "ismsap";
	while (fgets(chunk, sizeof(chunk), fp)) {
		cout << chunk;
		chunk[strcspn(chunk, "\r\n")] = 0;
		string chunkString = string(chunk);
		string newChunk = chunkString;
		cout << newChunk << endl;

		char* cstr = new char[newChunk.length() + 1];
		strcpy(cstr, newChunk.c_str());

		unsigned char digest[32];
		compute_sha256(cstr, digest);
		//unsigned char digestFinal[32];
		//sha256(digest, digestFinal);

		stringstream ss;
		for (int i = 0; i < 32; i++)
		{
			ss << hex << setw(2) << setfill('0') << (int)digest[i];
			fprintf(destinationFile, "%02X", digest[i]);
		}
		string sha256Result = ss.str();
		cout << sha256Result << endl;
		fprintf(destinationFile, "\n");

			
		delete[] cstr;
	}
	fclose(fp);
	fclose(destinationFile);
	
}