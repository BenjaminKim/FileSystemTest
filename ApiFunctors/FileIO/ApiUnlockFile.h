#pragma once


DEFINE_API_CLASS_BEGIN(UnlockFile)

BOOL operator()(
    __in  HANDLE hFile,
    __in  DWORD dwFileOffsetLow,
    __in  DWORD dwFileOffsetHigh,
    __in  DWORD nNumberOfBytesToUnlockLow,
    __in  DWORD nNumberOfBytesToUnlockHigh)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, dwFileOffsetLow);
    ADD_IN_PARAM(DWORD, dwFileOffsetHigh);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToUnlockLow);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToUnlockHigh);

    API_CALL_T(BOOL, UnlockFile,
        hFile,
        dwFileOffsetLow,
        dwFileOffsetHigh,
        nNumberOfBytesToUnlockLow,
        nNumberOfBytesToUnlockHigh);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()