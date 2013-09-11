#pragma once

#include "ApiWNetOpenEnum.h"

DEFINE_API_CLASS_DYN_BEGIN(WNetEnumResourceW, Mpr.dll)

static std::wstring GetString_lpBuffer(LPVOID lpBuffer, int count)
{
    std::wostringstream oss;
    LPNETRESOURCEW pInfo = (LPNETRESOURCEW)lpBuffer;

    while(count-- > 0)
    {
        oss << ApiWNetOpenEnumW::GetString_lpNetResource(pInfo++) << std::endl;
    }

    return oss.str();
}

DWORD operator()(
                 __in    HANDLE  hEnum,
                 __inout LPDWORD lpcCount,
                 __out_bcount(*lpBufferSize) LPVOID  lpBuffer,
                 __inout LPDWORD lpBufferSize)
{
    ADD_IN_PARAM(HANDLE, hEnum);
    ADD_IN_PARAM(PDWORD, lpcCount);
    ADD_IN_PARAM(PDWORD, lpBufferSize);

    API_DYN_CALL_T(DWORD, WNetEnumResourceW,
        hEnum,
        lpcCount,
        lpBuffer,
        lpBufferSize);

    if(returnValueT == NO_ERROR || returnValueT == ERROR_MORE_DATA || returnValueT == ERROR_NO_MORE_ITEMS)
    {
        ADD_OUT_PARAM(PDWORD, lpcCount);
        ADD_OUT_PARAM(_lpBuffer, lpBuffer, (int)*lpcCount);
        ADD_OUT_PARAM(PDWORD, lpBufferSize);
    }
    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(WNetEnumResourceW,
                         DWORD (__stdcall *)(
                         __in    HANDLE  hEnum,
                         __inout LPDWORD lpcCount,
                         __out_bcount(*lpBufferSize) LPVOID  lpBuffer,
                         __inout LPDWORD lpBufferSize)
                         )
