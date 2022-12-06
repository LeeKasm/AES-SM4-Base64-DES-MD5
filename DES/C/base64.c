#include "base64.h"



const char kBase64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


size_t base64_decodedLength(const char* in, size_t in_length) {

	int numEq = 0;

	const char* in_end = in + in_length;
	while (*--in_end == '=') ++numEq;

	return ((6 * in_length) / 8) - numEq;
}


size_t base64_encodedLength(size_t length) {

	return (length + 2 - ((length + 2) % 3)) / 3 * 4;
}


void base64_a3_to_a4(unsigned char* a4, unsigned char* a3) {

	a4[0] = (a3[0] & 0xfc) >> 2;
	a4[1] = ((a3[0] & 0x03) << 4) + ((a3[1] & 0xf0) >> 4);
	a4[2] = ((a3[1] & 0x0f) << 2) + ((a3[2] & 0xc0) >> 6);
	a4[3] = (a3[2] & 0x3f);
}


void base64_a4_to_a3(unsigned char* a3, unsigned char* a4) {

	a3[0] = (a4[0] << 2) + ((a4[1] & 0x30) >> 4);
	a3[1] = ((a4[1] & 0xf) << 4) + ((a4[2] & 0x3c) >> 2);
	a3[2] = ((a4[2] & 0x3) << 6) + a4[3];
}


unsigned char base64_lookup(unsigned char c) {

	if (c >= 'A' && c <= 'Z') return c - 'A';
	if (c >= 'a' && c <= 'z') return c - 71;
	if (c >= '0' && c <= '9') return c + 4;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return 255;
}


bool base64_encode(const char* input, size_t input_length, char* out, size_t out_length, size_t* encoded_length) {

	int i = 0, j = 0;
	char* out_begin = out;
	unsigned char a3[3];
	unsigned char a4[4];

	*encoded_length = base64_encodedLength(input_length);

	if (out == NULL || out_length < *encoded_length)
		return false;

	while (input_length--) {
		a3[i++] = *input++;
		if (i == 3) {
			base64_a3_to_a4(a4, a3);

			for (i = 0; i < 4; i++) {
				*out++ = kBase64Alphabet[a4[i]];
			}

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 3; j++) {
			a3[j] = '\0';
		}

		base64_a3_to_a4(a4, a3);

		for (j = 0; j < i + 1; j++) {
			*out++ = kBase64Alphabet[a4[j]];
		}

		while ((i++ < 3)) {
			*out++ = '=';
		}
	}

	return (out == (out_begin + *encoded_length));
}


bool base64_decode(const char* input, size_t input_length, char* out, size_t out_length, size_t* decoded_length) {

	int i = 0, j = 0;
	char* out_begin = out;
	unsigned char a3[3];
	unsigned char a4[4];

	*decoded_length = base64_decodedLength(input, input_length);

	if (out == NULL || out_length < *decoded_length)
		return false;

	while (input_length--) {
		if (*input == '=') {
			break;
		}

		a4[i++] = *(input++);
		if (i == 4) {
			for (i = 0; i < 4; i++) {
				a4[i] = base64_lookup(a4[i]);
			}

			base64_a4_to_a3(a3, a4);

			for (i = 0; i < 3; i++) {
				*out++ = a3[i];
			}

			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++) {
			a4[j] = '\0';
		}

		for (j = 0; j < 4; j++) {
			a4[j] = base64_lookup(a4[j]);
		}

		base64_a4_to_a3(a3, a4);

		for (j = 0; j < i - 1; j++) {
			*out++ = a3[j];
		}
	}

	return (out == (out_begin + *decoded_length));
}