#pragma once


DEFINE_API_CLASS_BEGIN(GetFileSize)

DWORD operator()(
    __in       HANDLE hFile,
    __out_opt  LPDWORD lpFileSizeHigh)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(DWORD, GetFileSize,
        hFile,
        lpFileSizeHigh);

    ADD_OUT_PARAM(PDWORD, lpFileSizeHigh);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()