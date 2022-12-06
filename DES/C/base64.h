#ifndef BASE64_H
#define BASE64_H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus


	bool base64_encode(const char* input, size_t input_length, char* out, size_t out_length, size_t* encoded_length);

	bool base64_decode(const char* input, size_t input_length, char* out, size_t out_length, size_t* decoded_length);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //BASE64_H