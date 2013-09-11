#pragma once


DEFINE_API_CLASS_BEGIN(GetFileAttributesEx)

static std::wstring GetString_fInfoLevelId(GET_FILEEX_INFO_LEVELS fInfoLevelId)
{
    SWITCH_BEGIN(fInfoLevelId)
        CASE(GetFileExInfoStandard)
        CASE(GetFileExMaxInfoLevel)
    SWITCH_END()
}

static std::wstring GetString_lpFileInformation(LPVOID lpFileInformation, GET_FILEEX_INFO_LEVELS fInfoLevelId)
{
    using namespace std;
    wostringstream oss;

    if(fInfoLevelId == GetFileExInfoStandard)
    {
        WIN32_FILE_ATTRIBUTE_DATA* pwfad = static_cast<WIN32_FILE_ATTRIBUTE_DATA*>(lpFileInformation);

        oss << L"dwFileAttributes -> " << pwfad->dwFileAttributes << endl;
        oss << L"ftCreationTime -> " << pwfad->ftCreationTime.dwHighDateTime << L" " << pwfad->ftCreationTime.dwLowDateTime << endl;
        oss << L"ftLastAccessTime -> " << pwfad->ftLastAccessTime.dwHighDateTime << L" " << pwfad->ftLastAccessTime.dwLowDateTime << endl;
        oss << L"ftLastWriteTime -> " << pwfad->ftLastWriteTime.dwHighDateTime << L" " << pwfad->ftLastWriteTime.dwLowDateTime << endl;

        INT64 jFileSize = pwfad->nFileSizeHigh;
        jFileSize <<= 32;
        jFileSize += pwfad->nFileSizeLow;
        oss << L"Filesize -> " << jFileSize;   
    }
    
    if(fInfoLevelId == GetFileExMaxInfoLevel)
    {
        oss << L"?????";
    }

    return oss.str();
}

BOOL operator()(
    __in   LPCTSTR lpFileName,
    __in   GET_FILEEX_INFO_LEVELS fInfoLevelId,
    __out  LPVOID lpFileInformation)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(_fInfoLevelId, fInfoLevelId);

    API_CALL_T(BOOL, GetFileAttributesExW,
        lpFileName,
        fInfoLevelId,
        lpFileInformation);

    ADD_OUT_PARAM(_lpFileInformation, lpFileInformation, fInfoLevelId);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()