#include "des.h"
#include <string.h>


//********** Private *************
char m_keyNum = 1;
char m_keyLen = 8;
char m_key[24] = { 0 };
char m_iv[8] = { 0 };
char m_cvec[8] = { 0 };   // 扭转向量
char m_subKey[3][16][48] = { { { 0 } } }; // 秘钥
PaddingMode m_paddingMode = PKCS7;
CipherMode m_cipherMode = CBC;


// initial permutation IP
const char IP_Table[64] = {
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};


// final permutation IP^-1
const char IPR_Table[64] = {
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25
};


// expansion operation matrix
const char E_Table[48] = {
	32,  1,  2,  3,  4,  5,  4,  5,  6,  7,  8,  9,
	8,  9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32,  1
};


// 32-bit permutation function P used on the output of the S-boxes
const char P_Table[32] = {
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	2,  8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25
};


// permuted choice table (key)
const char PC1_Table[56] = {
	57, 49, 41, 33, 25, 17,  9,  1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27, 19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,  7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29, 21, 13,  5, 28, 20, 12,  4
};


// permuted choice key (table)
const char PC2_Table[48] = {
	14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};


// number left rotations of pc1
const char LOOP_Table[16] = {
	1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
};


// The (in)famous S-boxes
const char S_Box[8][4][16] = {
	// S1
	{
		{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
		{0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
		{4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0},
		{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
	},
	// S2
	{
		{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
		{3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
		{0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
		{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
	},
	// S3
	{
		{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
		{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
		{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
		{1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
	},
	// S4
	{
		{7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
		{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
		{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
		{3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
	},
	// S5
	{
		{2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
		{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
		{4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
		{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3},
	},
	// S6
	{
		{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
		{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
		{9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
		{4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13},
	},
	// S7
	{
		{4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
		{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
		{1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
		{6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12},
	},
	// S8
	{
		{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
		{1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
		{7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
		{2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11},
	}
};


// 根据协议对加密前的数据进行填充
int des_padding(char* _Out, int* _OutLen, const char* _In, int _InLen, PaddingMode _Mode)
{
	char diff = 8 - (_InLen & 0x07);
	memcpy(_Out, _In, _InLen);
	switch (_Mode) {
	case PKCS7:
		memset(_Out + _InLen, diff, diff);
		break;
	case ISO1:
	case Zeros:
		if (8 == diff) {
			diff = 0;
		}
		memset(_Out + _InLen, 0x00, diff);
		break;
	case ANSIX923:
		memset(_Out + _InLen, 0x00, diff - 1);
		memset(_Out + _InLen + diff - 1, diff, 1);
		break;
	case ISO10126:
		memset(_Out + _InLen + diff - 1, diff, 1);
		break;
	case ISO2:
		memset(_Out + _InLen, 0x80, 1);
		memset(_Out + _InLen + 1, 0x00, diff - 1);
		break;
	case None:
	default:
		diff = 0;
		break;
	}
	*_OutLen = _InLen + diff;
	return 0;
}


// 根据协议对解密后的数据进行裁剪
int des_cutShort(const char* _In, int _InLen, PaddingMode _Mode)
{
	int cutLen = 0;
	int i = 0;
	switch (_Mode) {
	case PKCS7:
		cutLen = (char)_In[_InLen - 1];
		break;
	case ISO1:
	case Zeros:
		for (i = _InLen - 1; i >= 0; --i) {
			if (0x00 != _In[i]) {
				break;
			}
		}
		cutLen = _InLen - i;
		break;
	case ANSIX923:
		cutLen = _In[_InLen - 1];
		break;
	case ISO10126:
		cutLen = _In[_InLen - 1];
		break;
	case ISO2:
		for (i = _InLen - 1; i >= 0; --i) {
			if (0 == (_In[i] & 0x80)) {
				cutLen = _InLen - i + 1;
				break;
			}
		}
		break;
	case None:
	default:
		break;
	}
	return cutLen;
}


// 把BYTE转化为Bit流
void des_byteToBit(char* _Out, const char* _In, int _Bits)
{
	int i = 0;
	for (i = 0; i < _Bits; ++i) {
		_Out[i] = (_In[i >> 3] >> ((7 - i) & 7)) & 0x01;
	}
}


// 把Bit转化为Byte流
void des_bitToByte(char* _Out, const char* _In, int _Bits)
{
	int i = 0;
	memset(_Out, 0, _Bits >> 3);
	for (i = 0; i < _Bits; ++i) {
		_Out[i >> 3] |= _In[i] << ((7 - i) & 7);
	}
}


// 把两个Bit流按表进行位转化
void des_transform(char* _Out, char* _In, const char* _Table, int _Len)
{
	int i = 0;
	char temp[64];
	for (i = 0; i < _Len; ++i)
		temp[i] = _In[_Table[i] - 1];
	memcpy(_Out, temp, _Len);
}


// 把BIT流按位向左迭代
void des_rotateL(char* _In, int _Len, int _Loop)
{
	char temp[64];
	memcpy(temp, _In, _Loop);
	memcpy(_In, _In + _Loop, _Len - _Loop);
	memcpy(_In + _Len - _Loop, temp, _Loop);
}


// 计算并填充子密钥到SubKey数据中
void des_calcSubKey(char _SubKey[16][48], const char _Key[8])
{
	int i = 0;
	char K[64], * KL = &K[0], * KR = &K[28];
	des_byteToBit(K, _Key, 64);
	des_transform(K, K, PC1_Table, 56);
	for (i = 0; i < 16; ++i) {
		des_rotateL(KL, 28, LOOP_Table[i]);
		des_rotateL(KR, 28, LOOP_Table[i]);
		des_transform(_SubKey[i], K, PC2_Table, 48);
	}
}


// 异或运算
void des_XOR(char* _Out, const char* _In1, const char* _In2, int _Len)
{
	int i = 0;
	for (i = 0; i < _Len; ++i) {
		_Out[i] = _In1[i] ^ _In2[i];
	}
}


// 实现数据加密S BOX模块
void des_S_func(char _Out[32], const char _In[48])
{
	int i = 0, j = 0, k = 0, l = 0;
	for (i = 0, j = 0, k = 0; i < 8; ++i, _In += 6, _Out += 4) {
		j = (_In[0] << 1) + _In[5];
		k = (_In[1] << 3) + (_In[2] << 2) + (_In[3] << 1) + _In[4]; // 组织SID下标
		for (l = 0; l < 4; ++l) { // 把相应4bit赋值
			_Out[l] = (S_Box[i][j][k] >> (3 - l)) & 1;
		}
	}
}


// 实现数据加密到输出P
void des_F_func(char _In[32], const char _Ki[48])
{
	char MR[48];
	des_transform(MR, _In, E_Table, 48);
	des_XOR(MR, MR, _Ki, 48);
	des_S_func(_In, MR);
	des_transform(_In, _In, P_Table, 32);
}


// DES算法单元函数
void des_desUnit(char _Out[8], const char _In[8], const char _SubKey[16][48], DES_Method _Method)
{
	int i = 0;
	char M[64], tmp[32], * Li = &M[0], * Ri = &M[32];
	des_byteToBit(M, _In, 64);
	des_transform(M, M, IP_Table, 64);
	if (_Method == ENCRYPT) {
		for (i = 0; i < 16; ++i) {
			memcpy(tmp, Ri, 32);        // Ri[i-1] 保存
			des_F_func(Ri, _SubKey[i]);     // Ri[i-1]经过转化和SBox输出为P
			des_XOR(Ri, Ri, Li, 32);        // Ri[i] = P XOR Li[i-1]
			memcpy(Li, tmp, 32);        // Li[i] = Ri[i-1]
		}
	}
	else {
		for (i = 15; i >= 0; --i) {
			memcpy(tmp, Ri, 32);        // Ri[i-1] 保存
			des_F_func(Ri, _SubKey[i]);     // Ri[i-1]经过转化和SBox输出为P
			des_XOR(Ri, Ri, Li, 32);        // Ri[i] = P XOR Li[i-1]
			memcpy(Li, tmp, 32);        // Li[i] = Ri[i-1]
		}
	}
	des_rotateL(M, 64, 32);                 // Ri与Li换位重组M
	des_transform(M, M, IPR_Table, 64);     // 最后结果进行转化
	des_bitToByte(_Out, M, 64);             // 组织成字符
}


// ECB模式
void des_desForECB(char _Out[8], const char _In[8], DES_Method _Method)
{
	switch (m_keyNum) {
	case 1:
		des_desUnit(_Out, _In, (const char(*)[48])m_subKey[0], _Method);
		break;
	case 2:
		des_desUnit(_Out, _In, (const char(*)[48])m_subKey[0], _Method);
		des_desUnit(_Out, _Out, (const char(*)[48])m_subKey[1], !_Method);
		des_desUnit(_Out, _Out, (const char(*)[48])m_subKey[0], _Method);
		break;
	case 3:
	default:
		des_desUnit(_Out, _In, (const char(*)[48])m_subKey[DECRYPT == _Method ? 2 : 0], _Method);
		des_desUnit(_Out, _Out, (const char(*)[48])m_subKey[1], !_Method);
		des_desUnit(_Out, _Out, (const char(*)[48])m_subKey[DECRYPT == _Method ? 0 : 2], _Method);
		break;
	};
}


// CBC模式
void des_desForCBC(char _Out[8], const char _In[8], DES_Method _Method)
{
	//    char cvec[8] = {0}; // 扭转向量
	char cvin[8] = { 0 }; // 中间变量
	//    memcpy(cvec, m_iv, 8);
	if (_Method == ENCRYPT) {
		des_XOR(cvin, _In, m_cvec, 8);    // 将输入与扭转变量异或
	}
	else {
		memcpy(cvin, _In, 8);
	}
	des_desForECB(_Out, cvin, _Method);
	if (_Method == ENCRYPT) {
		memcpy(m_cvec, _Out, 8);      // 将输出设定为扭转变量
	}
	else {
		des_XOR(_Out, _Out, m_cvec, 8);   // 将输出与扭转变量异或
		memcpy(m_cvec, cvin, 8);      // 将输入设定为扭转变量
	}
}


typedef void (*DESForAnyCipherMode)(char _Out[8], const char _In[8], DES_Method _Method);
bool des_runDes(char* _Out, int* _OutLen, const char* _In, int _InLen, DES_Method _Method)
{
	if (_Out == NULL || *_OutLen < _InLen + 16) {

		*_OutLen = _InLen + 16;
		return false;
	}

	int i = 0, j = 0;
	char paddingData[16] = { 0 };
	int paddingLen = 0;
	DESForAnyCipherMode desForAnyCipherMode = des_desForECB;
	// 选择密码模式
	switch (m_cipherMode) {
	case ECB:
		desForAnyCipherMode = des_desForECB;
		break;
	case CBC:
		memcpy(m_cvec, m_iv, 8);
		desForAnyCipherMode = des_desForCBC;
		break;
	case OFB:
		break;
	case CFB:
		break;
	case CTS:
		break;
	default:
		break;
	}
	// 逐步加解密
	for (i = 0; i + 8 <= _InLen; i += 8) {
		desForAnyCipherMode(&_Out[i], &_In[i], _Method);
	}
	if (ENCRYPT == _Method) {
		// 数据扩充
		des_padding(paddingData, &paddingLen, &_In[i], _InLen & 0x07, m_paddingMode);
		for (j = 0; j + 8 <= paddingLen; j += 8) {
			desForAnyCipherMode(&_Out[i + j], &paddingData[j], _Method);
		}
		*_OutLen = i + j;
	}
	else {
		// 移除扩充的数据
		*_OutLen = i - des_cutShort(&_Out[i - 8], 8, m_paddingMode);
	}
	return true;
}
//********** Private *************



int des_setKey(const char* _Key, int _Len)
{
	int i = 0;
	char nKey = (_Len >> 3) >= 3 ? 3 : (_Len >> 3);
	for (i = 0; i < nKey; ++i) {
		des_calcSubKey(m_subKey[i], &_Key[i << 3]);
	}
	m_keyNum = nKey;
	m_keyLen = nKey << 3;
	memcpy(m_key, _Key, m_keyLen);
	return 0;
}


int des_setIV(const char* _IV, int _Len)
{
	if (8 == _Len) {
		memcpy(m_iv, _IV, 8);
	}
	return 0;
}


void des_setPaddingMode(PaddingMode _Mode)
{
	m_paddingMode = _Mode;
}


void des_setCipherMode(CipherMode _Mode)
{
	m_cipherMode = _Mode;
}


bool des_encrypt(const char* _In, int _InLen, char* _Out, int* _OutLen)
{
	return des_runDes(_Out, _OutLen, _In, _InLen, ENCRYPT);
}


bool des_decrypt(const char* _In, int _InLen, char* _Out, int* _OutLen)
{
	bool b = des_runDes(_Out, _OutLen, _In, _InLen, DECRYPT);
	if (b) {
		_Out[*_OutLen] = '\0';
	}
	return b;
}


void des_byteToHex(const char* _In, const int _InLen, char* _Out, const int _OutLen)
{
	int i = 0, j = 0;
	for (i = 0, j = 0; i < _InLen && j < _OutLen; ++i, ++j) {
		_Out[j] = (_In[i] >> 4) & 0x0F;
		_Out[j] += _Out[j] > 9 ? 55 : 48;
		_Out[++j] = _In[i] & 0x0F;
		_Out[j] += _Out[j] > 9 ? 55 : 48;
	}
}


void des_hexToByte(const char* _In, const int _InLen, char* _Out, const int _OutLen)
{
	int i = 0, j = 0;
	char temp = 0;
	for (i = 0, j = 0; i < _InLen && j < _OutLen; ++i, ++j) {
		temp = _In[i] > 57 ? _In[i] - 55 : _In[i] - 48;
		_Out[j] = (temp << 4) & 0xF0;
		temp = _In[++i] > 57 ? _In[i] - 55 : _In[i] - 48;
		_Out[j] += temp;
	}
}

