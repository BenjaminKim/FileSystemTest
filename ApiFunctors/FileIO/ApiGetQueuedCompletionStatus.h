#pragma once


DEFINE_API_CLASS_BEGIN(GetQueuedCompletionStatus)

BOOL operator()(
    __in   HANDLE CompletionPort,
    __out  LPDWORD lpNumberOfBytes,
    __out  PULONG_PTR lpCompletionKey,
    __out  LPOVERLAPPED *lpOverlapped,
    __in   DWORD dwMilliseconds)
{
    ADD_IN_PARAM(HANDLE, CompletionPort);
    ADD_IN_PARAM(DWORD, dwMilliseconds);

    API_CALL_T(BOOL, GetQueuedCompletionStatus,
        CompletionPort,
        lpNumberOfBytes,
        lpCompletionKey,
        lpOverlapped,
        dwMilliseconds);

    ADD_OUT_PARAM(PDWORD, lpNumberOfBytes);
    ADD_OUT_PARAM(PULONG, lpCompletionKey);
    ADD_OUT_PARAM(PVOID, lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()