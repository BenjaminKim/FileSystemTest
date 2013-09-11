#pragma once


DEFINE_API_CLASS_BEGIN(ReadFile)

BOOL operator()(
    __in         HANDLE hFile,
    __out        LPVOID lpBuffer,
    __in         DWORD nNumberOfBytesToRead,
    __out_opt    LPDWORD lpNumberOfBytesRead,
    __inout_opt  LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToRead);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, ReadFile,
        hFile,
        lpBuffer,
        nNumberOfBytesToRead,
        lpNumberOfBytesRead,
        lpOverlapped);

    ADD_OUT_PARAM(PVOID, lpBuffer);
    ADD_OUT_PARAM(PDWORD, lpNumberOfBytesRead);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()