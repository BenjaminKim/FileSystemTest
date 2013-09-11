#pragma once


DEFINE_API_CLASS_BEGIN(GetFileSizeEx)

BOOL operator()(
    __in  HANDLE hFile,
    __out PLARGE_INTEGER lpFileSize)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(BOOL, GetFileSizeEx,
        hFile,
        lpFileSize);

    ADD_OUT_PARAM(PLARGE_INTEGER, lpFileSize);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()