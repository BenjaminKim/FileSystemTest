#pragma once


DEFINE_API_CLASS_BEGIN(FindNextVolume)

BOOL operator()(
    __inout HANDLE hFindVolume,
    __out_ecount(cchBufferLength) LPWSTR lpszVolumeName,
    __in    DWORD cchBufferLength)
{
    ADD_IN_PARAM(HANDLE, hFindVolume);
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(BOOL, FindNextVolumeW,
        hFindVolume,
        lpszVolumeName,
        cchBufferLength);

    ADD_OUT_PARAM(PSTR, lpszVolumeName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()