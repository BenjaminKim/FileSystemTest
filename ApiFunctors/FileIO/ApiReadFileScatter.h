#pragma once


DEFINE_API_CLASS_BEGIN(ReadFileScatter)

BOOL operator()(
    __in        HANDLE hFile,
    __out       FILE_SEGMENT_ELEMENT aSegmentArray[],
    __in        DWORD nNumberOfBytesToRead,
    __reserved  LPDWORD lpReserved,
    __inout     LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, nNumberOfBytesToRead);
    ADD_IN_PARAM(PVOID, lpReserved);
    ADD_IN_PARAM(PVOID, lpOverlapped);

    API_CALL_T(BOOL, ReadFileScatter,
        hFile,
        aSegmentArray,
        nNumberOfBytesToRead,
        lpReserved,
        lpOverlapped);

    ADD_OUT_PARAM(PVOID, aSegmentArray);
    ADD_OUT_PARAM(PVOID, lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()