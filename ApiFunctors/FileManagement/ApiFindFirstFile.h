#pragma once

#include "ApiGetFileAttributes.h"


DEFINE_API_CLASS_BEGIN(FindFirstFile)

static std::wstring GetString_lpFindFileData(LPWIN32_FIND_DATA lpFindFileData)
{
    std::wostringstream oss;

    oss << L"dwFileAttributes -> " << GetString_dwFileAttributes(lpFindFileData->dwFileAttributes) << std::endl;
    oss << L"ftCreationTime -> " << FileTimeToString(lpFindFileData->ftCreationTime) << std::endl;
    oss << L"ftLastAccessTime -> " << FileTimeToString(lpFindFileData->ftLastAccessTime) << std::endl;
    oss << L"ftLastWriteTime -> " << FileTimeToString(lpFindFileData->ftLastWriteTime) << std::endl;
    oss << L"FileSize -> " << FileSizeToString(lpFindFileData->nFileSizeHigh, lpFindFileData->nFileSizeLow) << std::endl;
    oss << L"FileName -> " << lpFindFileData->cFileName << std::endl;
    oss << L"AlternateFileName -> " << lpFindFileData->cAlternateFileName << std::endl;

    return oss.str();
}

HANDLE operator()(
    __in   LPCTSTR lpFileName,
    __out  LPWIN32_FIND_DATA lpFindFileData)
{    
    std::wstring s = lpFileName;
    AddInParam(L"lpFileName", s.substr(1));

    API_CALL_T(HANDLE, FindFirstFileW,
        lpFileName,
        lpFindFileData);

    ADD_OUT_PARAM(_lpFindFileData, lpFindFileData);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()