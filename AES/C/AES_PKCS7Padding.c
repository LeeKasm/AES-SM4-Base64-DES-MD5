#include "AES_PKCS7Padding.h"



bool AES_CBC_PKCS7_ENCRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || strlen(key) != 16 || iv == NULL || strlen(iv) != 16 || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false;

	*returnSize = AES_PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	int padSuze = pkcs7_padding_pad_buffer(outputBuffer, inputSize, *returnSize, 16);
	int valid = pkcs7_padding_valid(outputBuffer, inputSize, *returnSize, 16);
	if (valid == false)
		return false;

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, outputBuffer, *returnSize);
	return true;
}


bool AES_CBC_PKCS7_DECRYPT(const char* key, const char* iv, uint8_t* inputBuffer, size_t inputSize, uint8_t* outputBuffer, size_t outputSize, size_t* returnSize) {

	if (key == NULL || strlen(key) != 16 || iv == NULL || strlen(iv) != 16 || inputBuffer == NULL || inputSize == 0 || returnSize == NULL)
		return false;

	*returnSize = AES_PADDING_OUT_SIZE(inputSize);

	if (outputBuffer == NULL || outputSize == 0 || outputSize < *returnSize)
		return false;

	memset(outputBuffer, 0, outputSize);
	memcpy(outputBuffer, inputBuffer, inputSize);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, outputBuffer, *returnSize);
	*returnSize = pkcs7_padding_data_length(outputBuffer, *returnSize, 16);
	return true;
}
