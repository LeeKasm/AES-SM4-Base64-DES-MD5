#include "AES_PKCS7Padding.h"



bool_x AES_CBC_PKCS7_ENCRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

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

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, outputBuffer, *returnSize);
	return true_x;
}


bool_x AES_CBC_PKCS7_DECRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || iv == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, outputBuffer, *returnSize);
	*returnSize = pkcs7_padding_data_length(outputBuffer, *returnSize, 16);
	return true_x;
}


bool_x AES_ECB_PKCS7_ENCRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

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

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	for (size_t i = 0; i < *returnSize; i += 16) {
		AES_ECB_encrypt(&ctx, outputBuffer + i);
	}
	return true_x;
}


bool_x AES_ECB_PKCS7_DECRYPT(const char* key, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false_x;

	*returnSize = PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false_x;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	struct AES_ctx ctx;
	AES_init_ctx(&ctx, key);
	for (size_t i = 0; i < *returnSize; i += 16) {
		AES_ECB_decrypt(&ctx, outputBuffer + i);
	}
	*returnSize = pkcs7_padding_data_length(outputBuffer, *returnSize, 16);
	return true_x;
}
