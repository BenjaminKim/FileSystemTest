#pragma once


DEFINE_API_CLASS_BEGIN(GetVolumeInformationByHandleW)

BOOL operator()(
    __in      HANDLE hFile,
    __out_ecount_opt(nVolumeNameSize) LPWSTR lpVolumeNameBuffer,
    __in      DWORD nVolumeNameSize,
    __out_opt LPDWORD lpVolumeSerialNumber,
    __out_opt LPDWORD lpMaximumComponentLength,
    __out_opt LPDWORD lpFileSystemFlags,
    __out_ecount_opt(nFileSystemNameSize) LPWSTR lpFileSystemNameBuffer,
    __in      DWORD nFileSystemNameSize)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, nVolumeNameSize);
    ADD_IN_PARAM(DWORD, nFileSystemNameSize);

    API_CALL_T(BOOL, GetVolumeInformationByHandleW,
        hFile,
        lpVolumeNameBuffer,
        nVolumeNameSize,
        lpVolumeSerialNumber,
        lpMaximumComponentLength,
        lpFileSystemFlags,
        lpFileSystemNameBuffer,
        nFileSystemNameSize);

    ADD_OUT_PARAM(PSTR, lpVolumeNameBuffer);
    ADD_OUT_PARAM(PDWORD, lpVolumeSerialNumber);
    ADD_OUT_PARAM(PDWORD, lpMaximumComponentLength);
    ADD_OUT_PARAM(PDWORD, lpFileSystemFlags);
    ADD_OUT_PARAM(PSTR, lpFileSystemNameBuffer);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()