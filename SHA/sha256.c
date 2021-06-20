#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

unsigned int rotateRight(unsigned int tmp, int num) {
	return tmp >> num | tmp << 32 - num;
}

int init(unsigned int *arr) {
	arr[0] = 0x6a09e667UL;
	arr[1] = 0xbb67ae85UL;
	arr[2] = 0x3c6ef372UL;
	arr[3] = 0xa54ff53aUL;
	arr[4] = 0x510e527fUL;
	arr[5] = 0x9b05688cUL;
	arr[6] = 0x1f83d9abUL;
	arr[7] = 0x5be0cd19UL;
	return 1;
}

static const unsigned int K256[64] = {
    0x428a2f98UL, 0x71374491UL, 0xb5c0fbcfUL, 0xe9b5dba5UL,
    0x3956c25bUL, 0x59f111f1UL, 0x923f82a4UL, 0xab1c5ed5UL,
    0xd807aa98UL, 0x12835b01UL, 0x243185beUL, 0x550c7dc3UL,
    0x72be5d74UL, 0x80deb1feUL, 0x9bdc06a7UL, 0xc19bf174UL,
    0xe49b69c1UL, 0xefbe4786UL, 0x0fc19dc6UL, 0x240ca1ccUL,
    0x2de92c6fUL, 0x4a7484aaUL, 0x5cb0a9dcUL, 0x76f988daUL,
    0x983e5152UL, 0xa831c66dUL, 0xb00327c8UL, 0xbf597fc7UL,
    0xc6e00bf3UL, 0xd5a79147UL, 0x06ca6351UL, 0x14292967UL,
    0x27b70a85UL, 0x2e1b2138UL, 0x4d2c6dfcUL, 0x53380d13UL,
    0x650a7354UL, 0x766a0abbUL, 0x81c2c92eUL, 0x92722c85UL,
    0xa2bfe8a1UL, 0xa81a664bUL, 0xc24b8b70UL, 0xc76c51a3UL,
    0xd192e819UL, 0xd6990624UL, 0xf40e3585UL, 0x106aa070UL,
    0x19a4c116UL, 0x1e376c08UL, 0x2748774cUL, 0x34b0bcb5UL,
    0x391c0cb3UL, 0x4ed8aa4aUL, 0x5b9cca4fUL, 0x682e6ff3UL,
    0x748f82eeUL, 0x78a5636fUL, 0x84c87814UL, 0x8cc70208UL,
    0x90befffaUL, 0xa4506cebUL, 0xbef9a3f7UL, 0xc67178f2UL
};

unsigned int* sha256(char* inputString) {
	unsigned int *hash = (unsigned int*)malloc(512);
	unsigned char *input = (unsigned char*)hash;
	unsigned int s0 = 0, s1 = 0;
	unsigned int maj = 0, ch = 0;
	unsigned int tmp1 = 0, tmp2 = 0;
	unsigned int h[8] = {0};
	unsigned int *t = (unsigned int*)malloc(32);
	int len = strlen(inputString);

	for(int i = 0; i < len; i ++)
		input[i] |= inputString[i];
	input[len] = 1 << 7;
	for(int i = 0; len * 8 >> 8; i ++, len >>= 8)
		input[63 - i] = 255 & len << 3;
	input[63] = len << 3 & 255;

	for(int i = 0; i < 64; i ++)
		hash[i] = htonl(hash[i]);

	init(h);
	init(t);

	for(int i = 16; i < 64; i ++) {
		s0 = rotateRight(hash[i - 15], 7) ^ rotateRight(hash[i - 15], 18) ^ hash[i - 15] >> 3;
		s1 = rotateRight(hash[i - 2], 17) ^ rotateRight(hash[i - 2], 19)  ^ hash[i - 2] >> 10;
		hash[i] = hash[i - 16] + s0 + hash[i - 7] + s1;
	}

	for(int i = 0; i < 64; i++) {
		s0 = rotateRight(t[0], 2) ^ rotateRight(t[0], 13) ^ rotateRight(t[0], 22);
		maj = (t[0] & t[1]) ^ (t[0] & t[2]) ^ (t[1] & t[2]);
		tmp2 = s0 + maj;

		s1 = rotateRight(t[4], 6) ^ rotateRight(t[4], 11) ^ rotateRight(t[4], 25);
		ch = (t[4] & t[5]) ^ (~t[4] & t[6]);
		tmp1 = t[7] + s1 + ch + K256[i] + hash[i];

		t[7] = t[6];
		t[6] = t[5];
		t[5] = t[4];
		t[4] = t[3] + tmp1;
		t[3] = t[2];
		t[2] = t[1];
		t[1] = t[0];
		t[0] = tmp1 + tmp2;
	}

	for(int i = 0; i < 8; i ++)
		t[i] += h[i];
	return t;
}

int main() {
	char *inputString = "hello world";
	unsigned int *tmp = sha256(inputString);
	for(int i = 0; i < 8; i ++)
		printf("%08X", tmp[i]);
	printf("\n");
	free(tmp);
}
