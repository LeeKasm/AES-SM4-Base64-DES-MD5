/* This is a public domain base64 implementation written by WEI Zhicheng. */

#include "Base64.h"

#define BASE64_PAD '='
#define BASE64DE_FIRST '+'
#define BASE64DE_LAST 'z'

/* BASE 64 encode table */
static const char base64en[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/',
};

/* ASCII order for BASE 64 decode, 255 in unused character */
static const unsigned char base64de[] = {
	/* nul, soh, stx, etx, eot, enq, ack, bel, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/*  bs,  ht,  nl,  vt,  np,  cr,  so,  si, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* dle, dc1, dc2, dc3, dc4, nak, syn, etb, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* can,  em, sub, esc,  fs,  gs,  rs,  us, */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/*  sp, '!', '"', '#', '$', '%', '&', ''', */
	   255, 255, 255, 255, 255, 255, 255, 255,

	/* '(', ')', '*', '+', ',', '-', '.', '/', */
	   255, 255, 255,  62, 255, 255, 255,  63,

	/* '0', '1', '2', '3', '4', '5', '6', '7', */
	    52,  53,  54,  55,  56,  57,  58,  59,

	/* '8', '9', ':', ';', '<', '=', '>', '?', */
	    60,  61, 255, 255, 255, 255, 255, 255,

	/* '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', */
	   255,   0,   1,  2,   3,   4,   5,    6,

	/* 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', */
	     7,   8,   9,  10,  11,  12,  13,  14,

	/* 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', */
	    15,  16,  17,  18,  19,  20,  21,  22,

	/* 'X', 'Y', 'Z', '[', '\', ']', '^', '_', */
	    23,  24,  25, 255, 255, 255, 255, 255,

	/* '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', */
	   255,  26,  27,  28,  29,  30,  31,  32,

	/* 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', */
	    33,  34,  35,  36,  37,  38,  39,  40,

	/* 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', */
	    41,  42,  43,  44,  45,  46,  47,  48,

	/* 'x', 'y', 'z', '{', '|', '}', '~', del, */
	    49,  50,  51, 255, 255, 255, 255, 255
};

size_t base64_encodedLength(size_t length) {

	return (length + 2 - ((length + 2) % 3)) / 3 * 4;
}

size_t base64_decodedLength(const char* in, size_t in_length) {

	int numEq = 0;

	const char* in_end = in + in_length;
	while (*--in_end == '=') ++numEq;

	return ((6 * in_length) / 8) - numEq;
}

int base64_encode(const char* input, size_t input_length, char* output, size_t out_length, size_t* encoded_length) {

	int s;
	unsigned int i;
	unsigned int j;
	unsigned char c;
	unsigned char l;

	if (input == NULL || input_length == 0 || encoded_length == NULL)
		return 0;

	*encoded_length = base64_encodedLength(input_length);

	if (output == NULL || out_length == 0 || out_length < *encoded_length)
		return 0;

	s = 0;
	l = 0;
	for (i = j = 0; i < input_length; i++) {
		c = input[i];

		switch (s) {
		case 0:
			s = 1;
			output[j++] = base64en[(c >> 2) & 0x3F];
			break;
		case 1:
			s = 2;
			output[j++] = base64en[((l & 0x3) << 4) | ((c >> 4) & 0xF)];
			break;
		case 2:
			s = 0;
			output[j++] = base64en[((l & 0xF) << 2) | ((c >> 6) & 0x3)];
			output[j++] = base64en[c & 0x3F];
			break;
		}
		l = c;
	}

	switch (s) {
	case 1:
		output[j++] = base64en[(l & 0x3) << 4];
		output[j++] = BASE64_PAD;
		output[j++] = BASE64_PAD;
		break;
	case 2:
		output[j++] = base64en[(l & 0xF) << 2];
		output[j++] = BASE64_PAD;
		break;
	}

	output[j] = 0;

	*encoded_length = j;

	return 1;
}

int base64_decode(const char* input, size_t input_length, char* output, size_t out_length, size_t* decoded_length) {

	unsigned int i;
	unsigned int j;
	unsigned char c;

	if (input == NULL || input_length == 0 || decoded_length == NULL)
		return 0;

	*decoded_length = base64_decodedLength(input, input_length);

	if (output == NULL || out_length == 0 || out_length < *decoded_length)
		return 0;

	if (input_length & 0x3) {
		return 0;
	}

	for (i = j = 0; i < input_length; i++) {
		if (input[i] == BASE64_PAD) {
			break;
		}
		if (input[i] < BASE64DE_FIRST || input[i] > BASE64DE_LAST) {
			return 0;
		}

		c = base64de[(unsigned char)input[i]];
		if (c == 255) {
			return 0;
		}

		switch (i & 0x3) {
		case 0:
			output[j] = (c << 2) & 0xFF;
			break;
		case 1:
			output[j++] |= (c >> 4) & 0x3;
			output[j] = (c & 0xF) << 4; 
			break;
		case 2:
			output[j++] |= (c >> 2) & 0xF;
			output[j] = (c & 0x3) << 6;
			break;
		case 3:
			output[j++] |= c;
			break;
		}
	}

	*decoded_length = j;

	return 1;
}
