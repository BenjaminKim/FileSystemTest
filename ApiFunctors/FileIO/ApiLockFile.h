#pragma once


DEFINE_API_CLASS_BEGIN(LockFile)

BOOL operator()(
    __in  HANDLE hFile,
    __in  DWORD dwFileOffsetLow,
    __in  DWORD dwFileOffsetHigh,
    __in  DWORD nNumberOfBytesToLockLow,
    __in  DWORD nNumberOfBytesToLockHigh)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, dwFileOffsetLow);
    ADD_IN_PARAM(DWORD, dwFileOffsetHigh);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToLockLow);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToLockHigh);

    API_CALL_T(BOOL, LockFile,
        hFile,
        dwFileOffsetLow,
        dwFileOffsetHigh,
        nNumberOfBytesToLockLow,
        nNumberOfBytesToLockHigh);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()