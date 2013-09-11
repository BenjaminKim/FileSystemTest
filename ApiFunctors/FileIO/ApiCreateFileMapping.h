#pragma once


DEFINE_API_CLASS_BEGIN(CreateFileMapping)

HANDLE operator()(
                __in      HANDLE hFile,
                __in_opt  LPSECURITY_ATTRIBUTES lpAttributes,
                __in      DWORD flProtect,
                __in      DWORD dwMaximumSizeHigh,
                __in      DWORD dwMaximumSizeLow,
                __in_opt  LPCTSTR lpName)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(PVOID, lpAttributes);
    ADD_IN_PARAM(DWORD, flProtect);
    ADD_IN_PARAM(DWORD, dwMaximumSizeHigh);
    ADD_IN_PARAM(DWORD, dwMaximumSizeLow);
    ADD_IN_PARAM(PSTR, lpName);

    API_CALL_T(HANDLE, CreateFileMapping,
        hFile,
        lpAttributes,
        flProtect,
        dwMaximumSizeHigh,
        dwMaximumSizeLow,
        lpName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()