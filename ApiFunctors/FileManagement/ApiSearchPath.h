#pragma once


DEFINE_API_CLASS_BEGIN(SearchPath)

BOOL operator()(
    __in_opt   LPCTSTR lpPath,
    __in       LPCTSTR lpFileName,
    __in_opt   LPCTSTR lpExtension,
    __in       DWORD nBufferLength,
    __out      LPTSTR lpBuffer,
    __out_opt  LPTSTR *lpFilePart)
{
    ADD_IN_PARAM(PSTR, lpPath);
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(PSTR, lpExtension);
    ADD_IN_PARAM(DWORD, nBufferLength);

    API_CALL_T(BOOL, SearchPath,
        lpPath,
        lpFileName,
        lpExtension,
        nBufferLength,
        lpBuffer,
        lpFilePart);

    ADD_OUT_PARAM(PSTR, lpBuffer);
    ADD_OUT_PARAM(PPSTR, lpFilePart);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()