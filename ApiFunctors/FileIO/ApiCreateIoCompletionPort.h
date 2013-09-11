#pragma once


DEFINE_API_CLASS_BEGIN(CreateIoCompletionPort)

HANDLE operator()(
    __in     HANDLE FileHandle,
    __in_opt HANDLE ExistingCompletionPort,
    __in     ULONG_PTR CompletionKey,
    __in     DWORD NumberOfConcurrentThreads)
{
    ADD_IN_PARAM(HANDLE, FileHandle);
    ADD_IN_PARAM(HANDLE, ExistingCompletionPort);
    ADD_IN_PARAM(ULONG_PTR, CompletionKey);
    ADD_IN_PARAM(DWORD, NumberOfConcurrentThreads);

    API_CALL_T(HANDLE, CreateIoCompletionPort,
        FileHandle,
        ExistingCompletionPort,
        CompletionKey,
        NumberOfConcurrentThreads);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()