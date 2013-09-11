#pragma once


DEFINE_API_CLASS_DYN_BEGIN(GetFinalPathNameByHandle, Kernel32.dll)

static std::wstring GetString_dwFlags(DWORD dwFlags)
{
    CHECK_BIT_BEGIN_HEX(dwFlags)

    // !!!!!
    // 매크로 수정되어야 함.
    CHECK_BIT(FILE_NAME_NORMALIZED)
    CHECK_BIT(FILE_NAME_OPENED)
    CHECK_BIT(VOLUME_NAME_DOS)
    CHECK_BIT(VOLUME_NAME_GUID)
    CHECK_BIT(VOLUME_NAME_NONE)
    CHECK_BIT(VOLUME_NAME_NT)

    CHECK_BIT_END()
}

BOOL operator()(
    __in   HANDLE hFile,
    __out  LPTSTR lpszFilePath,
    __in   DWORD cchFilePath,
    __in   DWORD dwFlags)
{
    // supported client : windows vista
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(DWORD, cchFilePath);
    ADD_IN_PARAM(_dwFlags, dwFlags);

    API_DYN_CALL_T(BOOL, GetFinalPathNameByHandle,
        hFile,
        lpszFilePath,
        cchFilePath,
        dwFlags);

    ADD_OUT_PARAM(PSTR, lpszFilePath);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(GetFinalPathNameByHandle,
    BOOL (__stdcall *)(
        HANDLE,
        LPTSTR,
        DWORD ,
        DWORD)
)