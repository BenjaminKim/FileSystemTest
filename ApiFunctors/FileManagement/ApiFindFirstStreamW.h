#pragma once


DEFINE_API_CLASS_BEGIN(FindFirstStreamW)

static std::wstring GetString_InfoLevel(STREAM_INFO_LEVELS InfoLevel)
{
    SWITCH_BEGIN(InfoLevel)
        CASE(FindStreamInfoStandard)
        CASE(FindStreamInfoMaxInfoLevel)
    SWITCH_END()
}

HANDLE operator()(
    __in        LPCWSTR lpFileName,
    __in        STREAM_INFO_LEVELS InfoLevel,
    __out       LPVOID lpFindStreamData,
    __reserved  DWORD dwFlags)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(_InfoLevel, InfoLevel);
    ADD_IN_PARAM(DWORD, dwFlags);

    API_CALL_T(HANDLE, FindFirstStreamW,
        lpFileName,
        InfoLevel,
        lpFindStreamData,
        dwFlags);

    ADD_OUT_PARAM(PVOID, lpFindStreamData);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()