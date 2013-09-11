#pragma once


DEFINE_API_CLASS_BEGIN(LockFileEx)

BOOL operator()(
    __in        HANDLE hFile,
    __in        DWORD dwFlags,
    __reserved  DWORD dwReserved,
    __in        DWORD nNumberOfBytesToLockLow,
    __in        DWORD nNumberOfBytesToLockHigh,
    __inout     LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, dwFlags);
    ADD_IN_PARAM(DWORD, dwReserved);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToLockLow);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToLockHigh);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, LockFileEx,
        hFile,
        dwFlags,
        dwReserved,
        nNumberOfBytesToLockLow,
        nNumberOfBytesToLockHigh,
        lpOverlapped);

    ADD_OUT_PARAM(PVOID, lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()