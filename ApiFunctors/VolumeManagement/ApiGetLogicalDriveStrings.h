#pragma once


DEFINE_API_CLASS_BEGIN(GetLogicalDriveStrings)

static std::wstring GetString_lpBuffer(LPWSTR lpBuffer, DWORD nBufferLength)
{
    std::wostringstream oss;
    size_t size;
    int length = nBufferLength;

    while(*lpBuffer && length > 0)
    {
        oss << L"[" << lpBuffer << L"], ";
        size = wcsnlen_s(lpBuffer, nBufferLength) + 1;
        lpBuffer += size;
        length -= size;
    }

    return oss.str();
}

DWORD operator()(
    __in DWORD nBufferLength,
    __out_ecount_part_opt(nBufferLength, return + 1) LPWSTR lpBuffer)
{
    ADD_IN_PARAM(DWORD, nBufferLength);

    API_CALL_T(DWORD, GetLogicalDriveStringsW,
        nBufferLength,
        lpBuffer);

    ADD_OUT_PARAM(_lpBuffer, lpBuffer, nBufferLength);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()