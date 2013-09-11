#pragma once


DEFINE_API_CLASS_BEGIN(UnlockFileEx)

BOOL operator()(
    __in        HANDLE hFile,
    __reserved  DWORD dwReserved,
    __in        DWORD nNumberOfBytesToUnlockLow,
    __in        DWORD nNumberOfBytesToUnlockHigh,
    __inout     LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, dwReserved);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToUnlockLow);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToUnlockHigh);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, UnlockFileEx,
        hFile,
        dwReserved,
        nNumberOfBytesToUnlockLow,
        nNumberOfBytesToUnlockHigh,
        lpOverlapped);

    ADD_OUT_PARAM(PVOID, lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()