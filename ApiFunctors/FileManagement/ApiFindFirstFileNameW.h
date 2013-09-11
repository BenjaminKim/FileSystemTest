#pragma once


DEFINE_API_CLASS_DYN_BEGIN(FindFirstFileNameW, Kernel32.dll)

HANDLE operator()(
    __in     LPCWSTR lpFileName,
    __in     DWORD dwFlags,
    __inout  LPDWORD StringLength,
    __inout  PWCHAR LinkName)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(DWORD, dwFlags);
    ADD_IN_PARAM(PDWORD, StringLength);
    ADD_IN_PARAM(PSTR, LinkName);

    API_DYN_CALL_T(HANDLE, FindFirstFileNameW,
        lpFileName,
        dwFlags,
        StringLength,
        LinkName);

    ADD_OUT_PARAM(PDWORD, StringLength);
    ADD_OUT_PARAM(PSTR, LinkName);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(FindFirstFileNameW,
    HANDLE (__stdcall *)(
        LPCWSTR,
        DWORD,
        LPDWORD,
        PWCHAR)
)