#pragma once


DEFINE_API_CLASS_BEGIN(GetFileInformationByHandle)

static std::wstring GetString_lpFileInformation(LPBY_HANDLE_FILE_INFORMATION lpFileInformation)
{
    DWORD    dwFileAttributes = lpFileInformation->dwFileAttributes;
    FILETIME ftCreationTime = lpFileInformation->ftCreationTime;
    FILETIME ftLastAccessTime = lpFileInformation->ftLastAccessTime;
    FILETIME ftLastWriteTime = lpFileInformation->ftLastWriteTime;
    DWORD    dwVolumeSerialNumber = lpFileInformation->dwVolumeSerialNumber;
    DWORD    nFileSizeHigh = lpFileInformation->nFileSizeHigh;
    DWORD    nFileSizeLow = lpFileInformation->nFileSizeLow;
    DWORD    nNumberOfLinks = lpFileInformation->nNumberOfLinks;
    DWORD    nFileIndexHigh = lpFileInformation->nFileIndexHigh;
    DWORD    nFileIndexLow = lpFileInformation->nFileIndexLow;

    std::wostringstream oss;
    oss << L"dwFileAttributs ->" << dwFileAttributes << std::endl;
    oss << L"dwVolumeSerialNumber ->" << dwVolumeSerialNumber << std::endl;
    oss << L"nFileSizeHigh ->" << nFileSizeHigh << std::endl;
    oss << L"nFileSizeLow ->" << nFileSizeLow << std::endl;
    oss << L"nNumberOfLinks ->" << nNumberOfLinks << std::endl;
    oss << L"nFileIndexHigh ->" << nFileIndexHigh << std::endl;
    oss << L"nFileIndexLow ->" << nFileIndexLow << std::endl;

    oss << L"CreationTime -> " << ::GetString_FileTime(&ftCreationTime) << std::endl;
    oss << L"LastAccessTime -> " << ::GetString_FileTime(&ftLastAccessTime) << std::endl;
    oss << L"ftLastWriteTime -> " << ::GetString_FileTime(&ftLastWriteTime) << std::endl;

    return oss.str();
}

BOOL operator()(
    __in   HANDLE hFile,
    __out  LPBY_HANDLE_FILE_INFORMATION lpFileInformation)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(BOOL, GetFileInformationByHandle,
        hFile,
        lpFileInformation);

    ADD_OUT_PARAM(_lpFileInformation, lpFileInformation);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()