#include <Windows.h>
#include "MD5_Utils.h"



char* EncryptMD5(const char* encryptString) {

    bool success = true;
    wchar_t* outWBuffer = NULL;
    int outWBufferLength = 0;
    char* outUTF8Buffer = NULL;
    int outUTF8BufferLength = 0;
    uint8_t* outMD5Buffer = NULL;
    size_t outMD5BufferLength = 0;
    char* outBuffer = NULL;
    size_t outBufferLength = 0;

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

    success = md5String((uint8_t*)outUTF8Buffer, strlen(outUTF8Buffer), NULL, 0, &outMD5BufferLength);
    outMD5Buffer = new uint8_t[outMD5BufferLength + 1];
    success = md5String((uint8_t*)outUTF8Buffer, strlen(outUTF8Buffer), outMD5Buffer, outMD5BufferLength, &outMD5BufferLength);
    if (!success) {
        goto End;
    }
    outMD5Buffer[outMD5BufferLength] = '\0';

    outBufferLength = outMD5BufferLength * 2;
    outBuffer = new char[outBufferLength + 1];
    memset(outBuffer, 0, outBufferLength + 1);
    for (size_t i = 0; i < outMD5BufferLength; i++) {
        char tmp[3] = { 0 };
        sprintf_s(tmp, 3, "%02X", outMD5Buffer[i]);
        strcat_s(outBuffer, outBufferLength + 1, tmp);
    }
    outBuffer[outBufferLength] = '\0';

End:
    if (outWBuffer) {
        delete[] outWBuffer;
        outWBuffer = NULL;
    }

    if (outUTF8Buffer) {
        delete[] outUTF8Buffer;
        outUTF8Buffer = NULL;
    }

    if (outMD5Buffer) {
        delete[] outMD5Buffer;
        outMD5Buffer = NULL;
    }

    if (!success && outBuffer) {
        delete[] outBuffer;
        outBuffer = NULL;
    }

    return outBuffer;
}