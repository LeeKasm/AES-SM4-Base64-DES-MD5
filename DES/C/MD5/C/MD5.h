#ifndef MD5_H
#define MD5_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

	
	typedef struct{
		uint64_t size;        // Size of input in bytes
		uint32_t buffer[4];   // Current accumulation of hash
		uint8_t input[64];    // Input to be used in the next step
		uint8_t digest[16];   // Result of algorithm
	}MD5Context;
	
	void md5Init(MD5Context *ctx);
	void md5Update(MD5Context *ctx, uint8_t * input_buffer, size_t input_len);
	void md5Finalize(MD5Context *ctx);
	void md5Step(uint32_t *buffer, uint32_t *input);

	int md5String(uint8_t* input_buffer, size_t input_size, uint8_t* output_buffer, size_t output_size, size_t* return_size);
	uint8_t* md5File(FILE *file);

	uint32_t F(uint32_t X, uint32_t Y, uint32_t Z);
	uint32_t G(uint32_t X, uint32_t Y, uint32_t Z);
	uint32_t H(uint32_t X, uint32_t Y, uint32_t Z);
	uint32_t I(uint32_t X, uint32_t Y, uint32_t Z);

	uint32_t rotateLeft(uint32_t x, uint32_t n);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif // !MD5_H