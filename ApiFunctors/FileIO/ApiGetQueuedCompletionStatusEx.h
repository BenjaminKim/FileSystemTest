#pragma once


DEFINE_API_CLASS_BEGIN(GetQueuedCompletionStatusEx)

BOOL operator()(
    __in   HANDLE CompletionPort,
    __out  LPOVERLAPPED_ENTRY lpCompletionPortEntries,
    __in   ULONG ulCount,
    __out  PULONG ulNumEntriesRemoved,
    __in   DWORD dwMilliseconds,
    __in   BOOL fAlertable)
{
    ADD_IN_PARAM(HANDLE, CompletionPort);
    ADD_IN_PARAM(ULONG, ulCount);
    ADD_IN_PARAM(DWORD, dwMilliseconds);
    ADD_IN_PARAM(BOOL, fAlertable);

    API_CALL_T(BOOL, GetQueuedCompletionStatusEx,
        CompletionPort,
        lpCompletionPortEntries,
        ulCount,
        ulNumEntriesRemoved,
        dwMilliseconds,
        fAlertable);

    ADD_OUT_PARAM(PVOID, lpCompletionPortEntries);
    ADD_OUT_PARAM(PULONG, ulNumEntriesRemoved);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()