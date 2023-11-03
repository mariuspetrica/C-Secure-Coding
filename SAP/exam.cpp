
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


void main() {

	FILE* sourceFile = NULL;
	FILE* destinationFile = NULL;
	AES_KEY key;
	unsigned char* buffer;
	unsigned char* data;
	int inputSize = 0;
	int outputSize = 0; // should be original size of the file - i have put a random number here
	//unsigned char iv[16];
	//memset(&iv, 0x01, sizeof(iv));
	unsigned char myIV[] = {0xff, 0xff, 0xff, 0xff, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12};
	unsigned char myKey[] = { 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x08, 0x07, 0x06, 0x05, 0x00, 0x00, 0x00, 0x00 };
	AES_set_decrypt_key(myKey, 128, &key);
	fopen_s(&sourceFile, "encrypted.txt", "rb");
	fopen_s(&destinationFile, "decrypted.txt", "wb");
	fseek(sourceFile, 0, SEEK_END);
	inputSize = ftell(sourceFile);
	//inputSize = ftell(sourceFile) - 4; if the original size is written within the file
	fseek(sourceFile, 0, SEEK_SET);
	//fread(&outputSize, sizeof(outputSize), 1, sourceFile); to get the original size of the file if it is written within the file
	outputSize = inputSize; // not okay, i need to know the original file size - assume i can take it from within the code after initial encryption
	buffer = (unsigned char*)malloc(inputSize);
	data = (unsigned char*)malloc(inputSize);
	memset(buffer, 0x00, inputSize);
	fread(buffer, inputSize, 1, sourceFile);

	AES_cbc_encrypt(buffer, data, inputSize, &key, myIV, AES_DECRYPT);
	fwrite(data, outputSize, 1, destinationFile);
	free(buffer);
	free(data);
	fclose(destinationFile);
	fclose(sourceFile);

}