#pragma once


DEFINE_API_CLASS_BEGIN(GetFileAttributes)

static std::wstring GetString_ReturnValue(DWORD dwFileAttributes)
{
    return GetString_dwFileAttributes(dwFileAttributes);
}

DWORD operator()(
    __in LPCWSTR lpFileName)
{
    ADD_IN_PARAM(PSTR, lpFileName);

    API_CALL_C(DWORD, GetFileAttributes,
        lpFileName);

    API_RETURN_C();
}

DEFINE_API_CLASS_END()