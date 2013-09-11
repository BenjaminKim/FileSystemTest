#pragma once


DEFINE_API_CLASS_BEGIN(FindFirstVolume)

HANDLE operator()(
    __out_ecount(cchBufferLength) LPWSTR lpszVolumeName,
    __in DWORD cchBufferLength)
{
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(HANDLE, FindFirstVolumeW,
        lpszVolumeName,
        cchBufferLength);

    ADD_OUT_PARAM(PSTR, lpszVolumeName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()