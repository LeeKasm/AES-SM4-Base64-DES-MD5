#ifndef DES_H
#define DES_H


#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
	// 摘要:
	//     不填充。
	None = 1,
	//
	// 摘要:
	//     PKCS #7 填充字符串由一个字节序列组成，每个字节填充该字节序列的长度。
	PKCS7 = 2,
	//
	// 摘要:
	//     填充字符串由设置为零的字节组成。
	Zeros = 3,
	//
	// 摘要:
	//     ANSIX923 填充字符串由一个字节序列组成，此字节序列的最后一个字节填充字节序列的长度，其余字节均填充数字零。
	ANSIX923 = 4,
	//
	// 摘要:
	//     ISO10126 填充字符串由一个字节序列组成，此字节序列的最后一个字节填充字节序列的长度，其余字节填充随机数据。
	ISO10126 = 5,
	ISO1 = 6,
	ISO2 = 7,
}PaddingMode;

typedef enum {
	// 摘要:
	//     密码块链 (CBC) 模式引入了反馈。每个纯文本块在加密前，通过按位“异或”操作与前一个块的密码文本结合。这样确保了即使纯文本包含许多相同的块，这些块中的每一个也会加密为不同的密码文本块。在加密块之前，初始化向量通过按位“异或”操作与第一个纯文本块结合。如果密码文本块中有一个位出错，相应的纯文本块也将出错。此外，后面的块中与原出错位的位置相同的位也将出错。
	CBC = 1,
	//
	// 摘要:
	//     电子密码本 (ECB) 模式分别加密每个块。这意味着任何纯文本块只要相同并且在同一消息中，或者在用相同的密钥加密的不同消息中，都将被转换成同样的密码文本块。如果要加密的纯文本包含大量重复的块，则逐块破解密码文本是可行的。另外，随时准备攻击的对手可能在您没有察觉的情况下替代和交换个别的块。如果密码文本块中有一个位出错，相应的整个纯文本块也将出错。
	ECB = 2,
	//
	// 摘要:
	//     输出反馈 (OFB) 模式将少量递增的纯文本处理成密码文本，而不是一次处理整个块。此模式与 CFB 相似；这两种模式的唯一差别是移位寄存器的填充方式不同。如果密码文本中有一个位出错，纯文本中相应的位也将出错。但是，如果密码文本中有多余或者缺少的位，则那个位之后的纯文本都将出错。
	OFB = 3,
	//
	// 摘要:
	//     密码反馈 (CFB) 模式将少量递增的纯文本处理成密码文本，而不是一次处理整个块。该模式使用在长度上为一个块且被分为几部分的移位寄存器。例如，如果块大小为
	//     8 个字节，并且每次处理一个字节，则移位寄存器被分为 8 个部分。如果密码文本中有一个位出错，则一个纯文本位出错，并且移位寄存器损坏。这将导致接下来若干次递增的纯文本出错，直到出错位从移位寄存器中移出为止。
	CFB = 4,
	//
	// 摘要:
	//     密码文本窃用 (CTS) 模式处理任何长度的纯文本并产生长度与纯文本长度匹配的密码文本。除了最后两个纯文本块外，对于所有其他块，此模式与 CBC
	//     模式的行为相同。
	CTS = 5,
}CipherMode;

typedef enum {
	ENCRYPT = 0,    //加密
	DECRYPT = 1,    //解密
}DES_Method;


#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus


	int des_setKey(const char* _Key, int _Len);

	int des_setIV(const char* _IV, int _Len);

	void des_setPaddingMode(PaddingMode _Mode);

	void des_setCipherMode(CipherMode _Mode);


	bool des_encrypt(const char* _In, int _InLen, char* _Out, int* _OutLen);

	bool des_decrypt(const char* _In, int _InLen, char* _Out, int* _OutLen);

	void des_byteToHex(const char* _In, const int _InLen, char* _Out, const int _OutLen);

	void des_hexToByte(const char* _In, const int _InLen, char* _Out, const int _OutLen);


#ifdef __cplusplus
}
#endif //__cplusplus

#endif //DES_H
