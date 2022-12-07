#include "SM4_PKCS7Padding.h"



bool_x SM4_CBC_PKCS7_ENCRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || iv == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	int padSuze = pkcs7_padding_pad_buffer(outputBuffer, inputSize, *returnSize, 16);
	int valid = pkcs7_padding_valid(outputBuffer, inputSize, *returnSize, 16);
	if (valid == false_x)
		return false_x;

	sm4_context ctx;
	sm4_setkey_enc(&ctx, key);
	uint8_t ivTemp[16] = { 0 };
	memcpy_s(ivTemp, 16, iv, 16);
	sm4_crypt_cbc(&ctx, SM4_ENCRYPT, *returnSize, ivTemp, outputBuffer, outputBuffer);
	return true_x;
}


bool_x SM4_CBC_PKCS7_DECRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || iv == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	sm4_context ctx;
	sm4_setkey_dec(&ctx, key);
	uint8_t ivTemp[16] = { 0 };
	memcpy_s(ivTemp, 16, iv, 16);
	sm4_crypt_cbc(&ctx, SM4_DECRYPT, *returnSize, ivTemp, outputBuffer, outputBuffer);
	*returnSize = pkcs7_padding_data_length(outputBuffer, *returnSize, 16);
	return true_x;
}


bool_x SM4_ECB_PKCS7_ENCRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	int padSuze = pkcs7_padding_pad_buffer(outputBuffer, inputSize, *returnSize, 16);
	int valid = pkcs7_padding_valid(outputBuffer, inputSize, *returnSize, 16);
	if (valid == false_x)
		return false_x;

	sm4_context ctx;
	sm4_setkey_enc(&ctx, key);
	sm4_crypt_ecb(&ctx, SM4_ENCRYPT, *returnSize, outputBuffer, outputBuffer);
	return true_x;
}


bool_x SM4_ECB_PKCS7_DECRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	sm4_context ctx;
	sm4_setkey_dec(&ctx, key);
	sm4_crypt_ecb(&ctx, SM4_DECRYPT, *returnSize, outputBuffer, outputBuffer);
	*returnSize = pkcs7_padding_data_length(outputBuffer, *returnSize, 16);
	return true_x;
}
