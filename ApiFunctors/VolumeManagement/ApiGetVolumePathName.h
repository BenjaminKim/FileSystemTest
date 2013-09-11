#pragma once


DEFINE_API_CLASS_BEGIN(GetVolumePathName)

BOOL operator()(
    __in LPCWSTR lpszFileName,
    __out_ecount(cchBufferLength) LPWSTR lpszVolumePathName,
    __in DWORD cchBufferLength)
{
    ADD_IN_PARAM(PSTR, lpszFileName);
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(BOOL, GetVolumePathNameW,
        lpszFileName,
        lpszVolumePathName,
        cchBufferLength);

    ADD_OUT_PARAM(PSTR, lpszVolumePathName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()