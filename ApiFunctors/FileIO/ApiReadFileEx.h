#pragma once


DEFINE_API_CLASS_BEGIN(ReadFileEx)

BOOL operator()(
    __in       HANDLE hFile,
    __out_opt  LPVOID lpBuffer,
    __in       DWORD nNumberOfBytesToRead,
    __inout    LPOVERLAPPED lpOverlapped,
    __in_opt   LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToRead);
    ADD_IN_PARAM(PVOID, lpOverlapped);
    ADD_IN_PARAM(PVOID, lpCompletionRoutine);

    API_CALL_T(BOOL, ReadFileEx,
        hFile,
        lpBuffer,
        nNumberOfBytesToRead,
        lpOverlapped,
        lpCompletionRoutine);

    ADD_OUT_PARAM(PVOID, lpBuffer);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()