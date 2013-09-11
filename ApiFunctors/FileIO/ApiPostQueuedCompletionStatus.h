#pragma once


DEFINE_API_CLASS_BEGIN(PostQueuedCompletionStatus)

BOOL operator()(
    __in      HANDLE CompletionPort,
    __in      DWORD dwNumberOfBytesTransferred,
    __in      ULONG_PTR dwCompletionKey,
    __in_opt  LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, CompletionPort);
    ADD_IN_PARAM(DWORD, dwNumberOfBytesTransferred);
    ADD_IN_PARAM(ULONG_PTR, dwCompletionKey);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, PostQueuedCompletionStatus,
        CompletionPort,
        dwNumberOfBytesTransferred,
        dwCompletionKey,
        lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()