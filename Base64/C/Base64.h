#ifndef BASE64_H
#define BASE64_H


#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

	
	/*
	 * output is null-terminated encode string.
	 * encoded_length is output length, exclusive terminating `\0'
	 * return 0 means false, 1 means true
	 */
	int base64_encode(const char* input, size_t input_length, char* output, size_t out_length, size_t* encoded_length);

	/*
	 * return 0 means false, 1 means true
	 */
	int base64_decode(const char* input, size_t input_length, char* output, size_t out_length, size_t* decoded_length);


#ifdef __cplusplus
}
#endif

#endif /* BASE64_H */
