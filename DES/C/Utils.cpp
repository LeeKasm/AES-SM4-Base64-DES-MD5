#include <Windows.h>
#include "Utils.h"
#include "des.h"
#include "base64.h"



bool des_inited = false;
char des_key[9] = { 0 };
char des_iv[9] = { 0 };
void InitDES(const char* key, const char* iv) {

    if (!des_inited) {

        memcpy_s(des_key, 9, key, 8);
        memcpy_s(des_iv, 9, iv, 8);
        des_setKey(des_key, 8);
        des_setIV(des_iv, 8);
        des_setPaddingMode(PKCS7);
        des_setCipherMode(CBC);
        des_inited = true;
    }
}


char* EncryptDES(const char* encryptString) {

    bool success = true;
    wchar_t* outWBuffer = NULL;
    size_t outWBufferLength = 0;
    char* outUTF8Buffer = NULL;
    int outUTF8BufferLength = 0;
    char* outDESBuffer = NULL;
    int outDESBufferLength = 0;
    char* outBase64Buffer = NULL;
    size_t outBase64BufferLength = 0; 
    
    if (!des_inited) {
        return NULL;
    }

    success = ((outWBufferLength = MultiByteToWideChar(CP_ACP, 0, encryptString, -1, NULL, 0)) > 0);
    outWBuffer = new wchar_t[outWBufferLength];
    success = ((outWBufferLength = MultiByteToWideChar(CP_ACP, 0, encryptString, -1, outWBuffer, outWBufferLength)) > 0);
    if (!success) {
        goto End;
    }

    success = ((outUTF8BufferLength = WideCharToMultiByte(CP_UTF8, 0, outWBuffer, -1, NULL, 0, NULL, NULL)) > 0);
    outUTF8Buffer = new char[outUTF8BufferLength];
    success = ((outUTF8BufferLength = WideCharToMultiByte(CP_UTF8, 0, outWBuffer, -1, outUTF8Buffer, outUTF8BufferLength, NULL, NULL)) > 0);
    if (!success) {
        goto End;
    }

    success = des_encrypt(outUTF8Buffer, (int)strlen(outUTF8Buffer), NULL, &outDESBufferLength);
    outDESBuffer = new char[(size_t)outDESBufferLength + 1];
    success = des_encrypt(outUTF8Buffer, (int)strlen(outUTF8Buffer), outDESBuffer, &outDESBufferLength);
    if (!success) {
        goto End;
    }
    outDESBuffer[outDESBufferLength] = '\0';

    success = base64_encode(outDESBuffer, outDESBufferLength, NULL, 0, &outBase64BufferLength);
    outBase64Buffer = new char[outBase64BufferLength + 1];
    success = base64_encode(outDESBuffer, outDESBufferLength, outBase64Buffer, outBase64BufferLength, &outBase64BufferLength);
    if (!success) {
        goto End;
    }
    outBase64Buffer[outBase64BufferLength] = '\0';

End:
    if (outWBuffer) {
        delete[] outWBuffer;
        outWBuffer = NULL;
    }
    
    if (outUTF8Buffer) {
        delete[] outUTF8Buffer;
        outUTF8Buffer = NULL;
    }
    
    if (outDESBuffer) {
        delete[] outDESBuffer;
        outDESBuffer = NULL;
    }

    if (!success && outBase64Buffer) {
        delete[] outBase64Buffer;
        outBase64Buffer = NULL;
    }

    return outBase64Buffer;
}


char* DecryptDES(const char* decryptString) {

    bool success = true;
    char* outBase64Buffer = NULL;
    size_t outBase64BufferLength = 0; 
    char* outDESBuffer = NULL;
    int outDESBufferLength = 0;
    wchar_t* outWBuffer = NULL;
    size_t outWBufferLength = 0;
    char* outBuffer = NULL;
    int outBufferLength = 0;

    if (!des_inited) {
        return NULL;
    }

    success = base64_decode(decryptString, strlen(decryptString), NULL, 0, &outBase64BufferLength);
    outBase64Buffer = new char[outBase64BufferLength + 1];
    success = base64_decode(decryptString, strlen(decryptString), outBase64Buffer, outBase64BufferLength, &outBase64BufferLength);
    if (!success) {
        goto End;
    }
    outBase64Buffer[outBase64BufferLength] = '\0';

    success = des_decrypt(outBase64Buffer, (int)outBase64BufferLength, NULL, &outDESBufferLength);
    outDESBuffer = new char[(size_t)outDESBufferLength + 1];
    success = des_decrypt(outBase64Buffer, (int)outBase64BufferLength, outDESBuffer, &outDESBufferLength);
    if (!success) {
        goto End;
    }
    outDESBuffer[outDESBufferLength] = '\0';

    success = ((outWBufferLength = MultiByteToWideChar(CP_UTF8, 0, outDESBuffer, -1, NULL, 0)) > 0);
    outWBuffer = new wchar_t[outWBufferLength];
    success = ((outWBufferLength = MultiByteToWideChar(CP_UTF8, 0, outDESBuffer, -1, outWBuffer, outWBufferLength)) > 0);
    if (!success) {
        goto End;
    }
    
    success = ((outBufferLength = WideCharToMultiByte(CP_ACP, 0, outWBuffer, -1, NULL, 0, NULL, NULL)) > 0);
    outBuffer = new char[outBufferLength];
    success = ((outBufferLength = WideCharToMultiByte(CP_ACP, 0, outWBuffer, -1, outBuffer, outBufferLength, NULL, NULL)) > 0);
    if (!success) {
        goto End;
    }

End:
    if (outBase64Buffer) {
        delete[] outBase64Buffer;
        outBase64Buffer = NULL;
    }

    if (outDESBuffer) {
        delete[] outDESBuffer;
        outDESBuffer = NULL;
    }

    if (outWBuffer) {
        delete[] outWBuffer;
        outWBuffer = NULL;
    }

    if (!success && outBuffer) {
        delete[] outBuffer;
        outBuffer = NULL;
    }

    return outBuffer;
}