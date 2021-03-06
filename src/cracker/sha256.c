#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "sha256.h"

static unsigned char hash[SHA256_DIGEST_LENGTH];
static char encoded[SHA256_DIGEST_LENGTH*2];

unsigned char *sha256_hash (const void *data, unsigned long data_len, const void *salt, unsigned long salt_len, size_t *len) {
	SHA256_CTX c;

	 *len = SHA256_DIGEST_LENGTH;

	if (SHA256_Init(&c) != 1) {
		return NULL;
	}
	if (SHA256_Update(&c, salt, salt_len) != 1) {
		return NULL;
	}
	if (SHA256_Update(&c, data, data_len) != 1) {
		return NULL;
	}
	if (SHA256_Final(hash, &c) != 1) {
		return NULL;
	}
	return hash;

}


char *sha256_encode_hex (char *in, size_t *len) {
	int i;

    *len = SHA256_DIGEST_LENGTH * 2;

	for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
		sprintf(&encoded[i*2], "%02x", (uint8_t) in[i]);
	}
	return encoded;
}
