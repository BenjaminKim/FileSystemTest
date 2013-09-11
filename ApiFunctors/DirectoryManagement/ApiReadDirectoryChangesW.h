#pragma once


DEFINE_API_CLASS_BEGIN(ReadDirectoryChangesW)

BOOL operator()(
    __in         HANDLE hDirectory,
    __out        LPVOID lpBuffer,
    __in         DWORD nBufferLength,
    __in         BOOL bWatchSubtree,
    __in         DWORD dwNotifyFilter,
    __out_opt    LPDWORD lpBytesReturned,
    __inout_opt  LPOVERLAPPED lpOverlapped,
    __in_opt     LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
    ADD_IN_PARAM(HANDLE, hDirectory);
    ADD_IN_PARAM(DWORD, nBufferLength);
    ADD_IN_PARAM(BOOL, bWatchSubtree);
    ADD_IN_PARAM(DWORD, dwNotifyFilter);
    ADD_IN_PARAM(PVOID, lpOverlapped);
    ADD_IN_PARAM(PVOID, lpCompletionRoutine);

    API_CALL_T(BOOL, ReadDirectoryChangesW,
        hDirectory,
        lpBuffer,
        nBufferLength,
        bWatchSubtree,
        dwNotifyFilter,
        lpBytesReturned,
        lpOverlapped,
        lpCompletionRoutine);

    ADD_OUT_PARAM(PVOID, lpBuffer);
    ADD_OUT_PARAM(PVOID, lpOverlapped);
    ADD_OUT_PARAM(PDWORD, lpBytesReturned);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()