#pragma once


DEFINE_API_CLASS_BEGIN(FindNextVolumeMountPoint)

BOOL operator()(
    __in HANDLE hFindVolumeMountPoint,
    __out_ecount(cchBufferLength) LPWSTR lpszVolumeMountPoint,
    __in DWORD cchBufferLength)
{
    ADD_IN_PARAM(HANDLE, hFindVolumeMountPoint);
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(BOOL, FindNextVolumeMountPointW,
        hFindVolumeMountPoint,
        lpszVolumeMountPoint,
        cchBufferLength);

    ADD_OUT_PARAM(PSTR, lpszVolumeMountPoint);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()