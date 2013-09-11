#pragma once


DEFINE_API_CLASS_BEGIN(GetBinaryType)

static std::wstring GetString_lpBinaryType(LPDWORD lpBinaryType)
{
    if(lpBinaryType)
    {
        SWITCH_BEGIN(*lpBinaryType)
            CASE(SCS_32BIT_BINARY)
            CASE(SCS_DOS_BINARY)
            CASE(SCS_WOW_BINARY)
            CASE(SCS_PIF_BINARY)
            CASE(SCS_POSIX_BINARY)
            CASE(SCS_OS216_BINARY)
            CASE(SCS_64BIT_BINARY)
        SWITCH_END()
    }
    return L"(NULL)";
}

BOOL operator()(
    __in   LPCTSTR lpApplicationName,
    __out  LPDWORD lpBinaryType)
{
    ADD_IN_PARAM(PSTR, lpApplicationName);

    API_CALL_T(BOOL, GetBinaryTypeW,
        lpApplicationName,
        lpBinaryType);

    ADD_OUT_PARAM(_lpBinaryType, lpBinaryType);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()