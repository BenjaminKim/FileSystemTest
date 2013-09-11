#pragma once


DEFINE_API_CLASS_BEGIN(GetFileType)

static std::wstring GetString_Result(DWORD dw)
{
    SWITCH_BEGIN(dw)
        CASE(FILE_TYPE_CHAR)
        CASE(FILE_TYPE_DISK)
        CASE(FILE_TYPE_PIPE)
        CASE(FILE_TYPE_REMOTE)
        CASE(FILE_TYPE_UNKNOWN)
    SWITCH_END()
}

DWORD operator()(
    __in  HANDLE hFile)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(DWORD, GetFileType,
        hFile);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()