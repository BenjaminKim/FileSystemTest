#pragma once


DEFINE_API_CLASS_BEGIN(GetFullPathName)

DWORD operator()(
    __in   LPCTSTR lpFileName,
    __in   DWORD nBufferLength,
    __out  LPTSTR lpBuffer,
    __out  LPTSTR *lpFilePart)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(DWORD, nBufferLength);

    API_CALL_T(DWORD, GetFullPathNameW,
        lpFileName,
        nBufferLength,
        lpBuffer,
        lpFilePart);

    ADD_OUT_PARAM(PSTR, lpBuffer);
    ADD_OUT_PARAM(PPSTR, lpFilePart);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()