
#include<iostream>
#include<openssl/sha.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/aes.h>
#include <string>
#include<string.h>
#include <openssl/applink.c>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

#define MESSAGE_CHUNK 256

void main() {

	ifstream file("aeskey.txt");

	string str;

	while (getline(file, str))
	{
		cout << str;
	}

	FILE* sourceFile = NULL;
	FILE* destinationFile = NULL;
	AES_KEY key;

	unsigned char* buffer = NULL;
	unsigned char* data = NULL;
	int fileSize = 0;
	int outputSize = 0;
	unsigned char iv[16];

	memset(&iv, 0x01, sizeof(iv));
	fopen_s(&sourceFile, "wordlist.txt", "rb");
	fopen_s(&destinationFile, "encrypted.txt", "wb");

	fseek(sourceFile, 0, SEEK_END);
	fileSize = ftell(sourceFile);
	fseek(sourceFile, 0, SEEK_SET);
	if ((fileSize % 16) == 0) {
		outputSize = fileSize;
	}
	else {
		outputSize = ((fileSize / 16) * 16) + 16;
	}
	buffer = (unsigned char*)malloc(outputSize);
	data = (unsigned char*)malloc(outputSize);
	memset(buffer, 0x00, outputSize);
	fread(buffer, fileSize, 1, sourceFile);

	AES_set_encrypt_key((const unsigned char*)"#Master-ISM2017#", 128, &key);

	AES_cbc_encrypt(buffer, data, outputSize, &key, iv, AES_ENCRYPT);
	fwrite(&fileSize, sizeof(fileSize), 1, destinationFile); // optional if you want to write the size of the file
	fwrite(data, outputSize, 1, destinationFile);
	free(buffer);
	free(data);
	fclose(destinationFile);
	fclose(sourceFile);


}