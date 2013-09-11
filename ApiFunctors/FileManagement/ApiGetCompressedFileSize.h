#pragma once


DEFINE_API_CLASS_BEGIN(GetCompressedFileSize)

DWORD operator()(
    __in       LPCTSTR lpFileName,
    __out_opt  LPDWORD lpFileSizeHigh)
{
    ADD_IN_PARAM(PSTR, lpFileName);

    API_CALL_T(DWORD, GetCompressedFileSizeW,
        lpFileName,
        lpFileSizeHigh);

    ADD_OUT_PARAM(PDWORD, lpFileSizeHigh);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()