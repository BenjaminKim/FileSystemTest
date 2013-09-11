#pragma once


DEFINE_API_CLASS_BEGIN(FindFirstVolumeMountPoint)

HANDLE operator()(
    __in LPCWSTR lpszRootPathName,
    __out_ecount(cchBufferLength) LPWSTR lpszVolumeMountPoint,
    __in DWORD cchBufferLength)
{
    ADD_IN_PARAM(PSTR, lpszRootPathName);
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(HANDLE, FindFirstVolumeMountPointW,
        lpszRootPathName,
        lpszVolumeMountPoint,
        cchBufferLength);

    if(returnValueT != INVALID_HANDLE_VALUE)
    {
        ADD_OUT_PARAM(PSTR, lpszVolumeMountPoint);
    }

    API_RETURN_T();
}

DEFINE_API_CLASS_END()