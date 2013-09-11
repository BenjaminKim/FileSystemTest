#pragma once


DEFINE_API_CLASS_BEGIN(WriteFileEx)

static std::wstring GetString_lpOverlapped(LPOVERLAPPED /*lpOverlapped*/)
{
    return L"";
}

static std::wstring GetString_lpCompletionRoutine(LPOVERLAPPED_COMPLETION_ROUTINE /*lpCompletionRoutine*/)
{
    return L"";
}

BOOL operator()(
    __in      HANDLE hFile,
    __in_opt  LPCVOID lpBuffer,
    __in      DWORD nNumberOfBytesToWrite,
    __inout   LPOVERLAPPED lpOverlapped,
    __in_opt  LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(PVOID, lpBuffer);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToWrite);
    ADD_IN_PARAM(_lpOverlapped, lpOverlapped);
    ADD_IN_PARAM(_lpCompletionRoutine, lpCompletionRoutine);

    API_CALL_T(BOOL, WriteFileEx,
        hFile,
        lpBuffer,
        nNumberOfBytesToWrite,
        lpOverlapped,
        lpCompletionRoutine);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()