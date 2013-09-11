#pragma once


DEFINE_API_CLASS_BEGIN(MoveFileEx)

static std::wstring GetString_dwFlags(DWORD dwFlags)
{
    CHECK_BIT_BEGIN_HEX(dwFlags)

    CHECK_BIT(MOVEFILE_REPLACE_EXISTING)
    CHECK_BIT(MOVEFILE_COPY_ALLOWED)
    CHECK_BIT(MOVEFILE_DELAY_UNTIL_REBOOT)
    CHECK_BIT(MOVEFILE_WRITE_THROUGH)
    CHECK_BIT(MOVEFILE_CREATE_HARDLINK)
    CHECK_BIT(MOVEFILE_FAIL_IF_NOT_TRACKABLE)

    CHECK_BIT_END()
}

BOOL operator()(
    __in     LPCWSTR lpExistingFileName,
    __in_opt LPCWSTR lpNewFileName,
    __in     DWORD   dwFlags)
{
    ADD_IN_PARAM(PSTR, lpExistingFileName);
    ADD_IN_PARAM(PSTR, lpNewFileName);
    ADD_IN_PARAM(_dwFlags, dwFlags);

    API_CALL_T(BOOL, MoveFileExW,
        lpExistingFileName,
        lpNewFileName,
        dwFlags);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()