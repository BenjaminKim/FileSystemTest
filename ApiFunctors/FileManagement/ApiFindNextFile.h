#pragma once

#include "ApiFindFirstFile.h"


DEFINE_API_CLASS_BEGIN(FindNextFile)

static std::wstring GetString_lpFindFileData(LPWIN32_FIND_DATA lpFindFileData)
{
    return ApiFindFirstFile::GetString_lpFindFileData(lpFindFileData);
}

BOOL operator()(
    __in   HANDLE hFindFile,
    __out  LPWIN32_FIND_DATA lpFindFileData)
{
    ADD_IN_PARAM(HANDLE, hFindFile);

    API_CALL_T(BOOL, FindNextFileW,
        hFindFile,
        lpFindFileData);

    ADD_OUT_PARAM(_lpFindFileData, lpFindFileData);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()