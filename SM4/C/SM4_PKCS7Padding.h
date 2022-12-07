#ifndef SM4_PKCS7PADDING_H
#define SM4_PKCS7PADDING_H

#ifdef __cplusplus
extern "C" {
#endif


#include "SM4.h"
#include "PKCS7Padding.h"

	bool_x SM4_CBC_PKCS7_ENCRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize);
	bool_x SM4_CBC_PKCS7_DECRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize);
	
	bool_x SM4_ECB_PKCS7_ENCRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize);
	bool_x SM4_ECB_PKCS7_DECRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize);


#ifdef __cplusplus
}
#endif

#endif /* SM4_PKCS7PADDING_H */
