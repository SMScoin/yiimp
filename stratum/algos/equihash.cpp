/**
 * Equihash solver interface for ccminer (compatible with linux and windows)
 * Solver taken from nheqminer, by djeZo (and NiceHash)
 * tpruvot - 2017 (GPL v3)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdexcept>

#include <sha3/sph_sha2.h>

#include "equihash.h" // equi_verify()


// All solutions (BLOCK_HEADER_LEN + SOLSIZE_LEN + SOL_LEN) sha256d should be under the target
extern "C" void equi_hash(const char* input, char* output, uint32_t len)
{
	uint8_t _ALIGN(64), hash0[32], hash1[32];

	sph_sha256_context ctx_sha256;

	sph_sha256_init(&ctx_sha256);
	sph_sha256(&ctx_sha256, input, len);
	sph_sha256_close(&ctx_sha256, hash0);
	sph_sha256(&ctx_sha256, hash0, 32);
	sph_sha256_close(&ctx_sha256, hash1);

	memcpy(output, hash1, 32);
}

