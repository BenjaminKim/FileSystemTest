#pragma once

#include "ApiGetFileInformationByHandle.h"


DEFINE_API_CLASS_DYN_BEGIN(GetFileInformationByHandleEx, Kernel32.dll)

static std::wstring GetString_FileInformationClass(FILE_INFO_BY_HANDLE_CLASS FileInformationClass)
{
    SWITCH_BEGIN(FileInformationClass)
        CASE(FileBasicInfo)
        CASE(FileStandardInfo)
        CASE(FileNameInfo)
        CASE(FileRenameInfo)
        CASE(FileDispositionInfo)
        CASE(FileAllocationInfo)
        CASE(FileEndOfFileInfo)
        CASE(FileStreamInfo)
        CASE(FileCompressionInfo)
        CASE(FileAttributeTagInfo)
        CASE(FileIdBothDirectoryInfo)
        CASE(FileIdBothDirectoryRestartInfo)
        CASE(FileIoPriorityHintInfo)
        CASE(MaximumFileInfoByHandleClass)
    SWITCH_END()
}

static std::wstring GetString_FileInformationData(
    FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation)
{
    SWITCH_BEGIN(FileInformationClass)
        case FileBasicInfo:
            oss << L"(FileBasicInfo) lpFileInformation = " << ::GetStringPVOID(lpFileInformation) << std::endl;
            if(lpFileInformation)
            {
                PFILE_BASIC_INFO pInfo = (PFILE_BASIC_INFO)lpFileInformation;
                FILETIME ft;

                ft.dwLowDateTime = pInfo->CreationTime.LowPart;
                ft.dwHighDateTime = pInfo->CreationTime.HighPart;
                oss << L"CreationTime -> " << ::GetString_FileTime(&ft) << std::endl;

                ft.dwLowDateTime = pInfo->LastAccessTime.LowPart;
                ft.dwHighDateTime = pInfo->LastAccessTime.HighPart;
                oss << L"LastAccessTime -> " << ::GetString_FileTime(&ft) << std::endl;

                ft.dwLowDateTime = pInfo->LastWriteTime.LowPart;
                ft.dwHighDateTime = pInfo->LastWriteTime.HighPart;
                oss << L"LastWriteTime -> " << ::GetString_FileTime(&ft) << std::endl;

                ft.dwLowDateTime = pInfo->ChangeTime.LowPart;
                ft.dwHighDateTime = pInfo->ChangeTime.HighPart;
                oss << L"ChangeTime -> " << ::GetString_FileTime(&ft) << std::endl;

                oss << L"dwFileAttributes -> " << ::GetString_dwFileAttributes(pInfo->FileAttributes) << std::endl;
            }
            return oss.str();

        CASE(FileStandardInfo)
        CASE(FileNameInfo)

        case FileRenameInfo:
            oss << L"(FileRenameInfo) lpFileInformation = " << ::GetStringPVOID(lpFileInformation) << std::endl;
            if(lpFileInformation)
            {
                PFILE_RENAME_INFO pInfo = (PFILE_RENAME_INFO)lpFileInformation;

                PWCHAR pFileName = new WCHAR[pInfo->FileNameLength + 1];
                wmemset(pFileName, 0, pInfo->FileNameLength + 1);
                oss << L"ReplaceIfExists -> " << ::GetStringBOOL(pInfo->ReplaceIfExists) << std::endl;
                oss << L"RootDirectory -> " << ::GetStringHANDLE(pInfo->RootDirectory) << std::endl;
                oss << L"FileNameLength -> " << ::GetStringDWORD(pInfo->FileNameLength) << std::endl;
                oss << L"FileName -> " << pFileName << std::endl;

                delete[] pFileName;
            }
            return oss.str();

        case FileDispositionInfo:
            oss << L"(FileDispositionInfo) lpFileInformation = " << ::GetStringPVOID(lpFileInformation) << std::endl;
            if(lpFileInformation)
            {
                PFILE_DISPOSITION_INFO pInfo = (PFILE_DISPOSITION_INFO)lpFileInformation;

                oss << L"DeleteFile -> " << ::GetStringBOOL(pInfo->DeleteFile) << std::endl;
            }
            return oss.str();

        CASE(FileAllocationInfo)
        CASE(FileEndOfFileInfo)
        CASE(FileStreamInfo)
        CASE(FileCompressionInfo)
        CASE(FileAttributeTagInfo)
        CASE(FileIdBothDirectoryInfo)
        CASE(FileIdBothDirectoryRestartInfo)
        CASE(FileIoPriorityHintInfo)
        CASE(MaximumFileInfoByHandleClass)
    SWITCH_END()
}

BOOL operator()(
    __in   HANDLE hFile,
    __in   FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    __out  LPVOID lpFileInformation,
    __in   DWORD dwBufferSize)
{
    // supported client : windows vista
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(_FileInformationClass, FileInformationClass);
    ADD_IN_PARAM(DWORD, dwBufferSize);

    API_DYN_CALL_T(BOOL, GetFileInformationByHandleEx,
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize);

    //ADD_OUT_PARAM(PVOID, lpFileInformation);
    ADD_OUT_PARAM(_FileInformationData, FileInformationClass, lpFileInformation);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(GetFileInformationByHandleEx,
    BOOL (__stdcall *)(
        HANDLE,
        FILE_INFO_BY_HANDLE_CLASS,
        LPVOID,
        DWORD)
)