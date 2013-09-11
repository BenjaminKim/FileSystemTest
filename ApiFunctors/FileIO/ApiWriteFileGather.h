#pragma once


DEFINE_API_CLASS_BEGIN(WriteFileGather)

BOOL operator()(
    __in        HANDLE hFile,
    __in        FILE_SEGMENT_ELEMENT aSegmentArray[],
    __in        DWORD nNumberOfBytesToWrite,
    __reserved  LPDWORD lpReserved,
    __inout     LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(PVOID, aSegmentArray);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToWrite);
    ADD_IN_PARAM(PVOID, lpReserved);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, WriteFileGather,
        hFile,
        aSegmentArray,
        nNumberOfBytesToWrite,
        lpReserved,
        lpOverlapped);

    ADD_OUT_PARAM(DWORD, nNumberOfBytesToWrite);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()