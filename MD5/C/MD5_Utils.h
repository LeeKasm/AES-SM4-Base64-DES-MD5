#ifndef MD5_UTILS_H
#define MD5_UTILS_H


#include <stdio.h>
#include <stdlib.h>
#include "MD5.h"


#ifdef __cplusplus


__declspec(dllexport) char* EncryptMD5(const char* encryptString);


#endif //__cplusplus

#endif //MD5_UTILS_H
