#pragma once


DEFINE_API_CLASS_BEGIN(WriteFile)

BOOL operator()(
    __in         HANDLE hFile,
    __in         LPCVOID lpBuffer,
    __in         DWORD nNumberOfBytesToWrite,
    __out_opt    LPDWORD lpNumberOfBytesWritten,
    __inout_opt  LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(PVOID, lpBuffer);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToWrite);
    ADD_IN_PARAM(PDWORD, lpNumberOfBytesWritten);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, WriteFile,
        hFile,
        lpBuffer,
        nNumberOfBytesToWrite,
        lpNumberOfBytesWritten,
        lpOverlapped);

    ADD_OUT_PARAM(PDWORD, lpNumberOfBytesWritten);
    ADD_OUT_PARAM(PVOID, lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()