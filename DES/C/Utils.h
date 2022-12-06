#ifndef ANDROIDHOOKER_UTILS_H
#define ANDROIDHOOKER_UTILS_H


#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus


__declspec(dllexport) void InitDES(const char* key, const char* iv);
__declspec(dllexport) char* EncryptDES(const char* encryptString);
__declspec(dllexport) char* DecryptDES(const char* decryptString);


#endif //__cplusplus

#endif //ANDROIDHOOKER_UTILS_H
