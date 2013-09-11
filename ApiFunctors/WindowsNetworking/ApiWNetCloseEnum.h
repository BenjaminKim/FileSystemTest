#pragma once


DEFINE_API_CLASS_DYN_BEGIN(WNetCloseEnum, Mpr.dll)

DWORD operator()(
                 __in HANDLE   hEnum)
{
    ADD_IN_PARAM(HANDLE, hEnum);

    API_DYN_CALL_T(DWORD, WNetCloseEnum,
        hEnum);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(WNetCloseEnum,
                         DWORD (__stdcall *)(
                         __in HANDLE   hEnum)
                         )