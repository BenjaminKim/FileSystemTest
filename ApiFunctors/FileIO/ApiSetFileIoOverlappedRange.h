#pragma once


DEFINE_API_CLASS_BEGIN(SetFileIoOverlappedRange)

BOOL operator()(
    __in HANDLE FileHandle,
    __in PUCHAR OverlappedRangeStart,
    __in ULONG Length)
{
    ADD_IN_PARAM(HANDLE, FileHandle);
    ADD_IN_PARAM(PVOID, OverlappedRangeStart);
    ADD_IN_PARAM(ULONG, Length);

    API_CALL_T(BOOL, SetFileIoOverlappedRange,
        FileHandle,
        OverlappedRangeStart,
        Length);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()