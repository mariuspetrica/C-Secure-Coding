
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
	unsigned char messageData[SHA256_DIGEST_LENGTH];
	SHA256_CTX ctx;
	SHA256_Init(&ctx);
	int plainTextFileLength = 0;
	FILE* sourceFile = NULL;
	unsigned char* buffer = NULL;
	fopen_s(&sourceFile, "wordlist.txt", "rb");
	fseek(sourceFile, 0, SEEK_END);
	plainTextFileLength = ftell(sourceFile);
	fseek(sourceFile, 0, SEEK_SET);
	buffer = (unsigned char*)malloc(plainTextFileLength);
	fread(buffer, plainTextFileLength, 1, sourceFile);
	unsigned char* temporarBuffer = buffer;
	while (plainTextFileLength > 0) {
		if (plainTextFileLength > MESSAGE_CHUNK) {
			SHA256_Update(&ctx, temporarBuffer, MESSAGE_CHUNK);
		}
		else {
			SHA256_Update(&ctx, temporarBuffer, plainTextFileLength);
		}
		plainTextFileLength -= MESSAGE_CHUNK;
		temporarBuffer += MESSAGE_CHUNK;
	}
	free(buffer);
	fclose(sourceFile);
	SHA256_Final(messageData, &ctx);

	printf("\nSHA1 = ");
	for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
		printf("%02X ", messageData[i]);
		printf(" ");
	}
	printf("\n\n");

}