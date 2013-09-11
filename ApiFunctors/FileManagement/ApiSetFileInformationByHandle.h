#pragma once

#include "ApiGetFileInformationByHandleEx.h"


DEFINE_API_CLASS_DYN_BEGIN(SetFileInformationByHandle, Kernel32.dll)

static std::wstring GetString_FileInformationClass(FILE_INFO_BY_HANDLE_CLASS FileInformationClass)
{
    return ApiGetFileInformationByHandleEx::GetString_FileInformationClass(FileInformationClass);
}

static std::wstring GetString_FileInformationData(
    FILE_INFO_BY_HANDLE_CLASS FileInformationClass, LPVOID lpFileInformation)
{
    return ApiGetFileInformationByHandleEx::GetString_FileInformationData(FileInformationClass, lpFileInformation);
}

BOOL operator()(
    __in  HANDLE hFile,
    __in  FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
    __in  LPVOID lpFileInformation,
    __in  DWORD dwBufferSize)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(_FileInformationClass, FileInformationClass);
    ADD_IN_PARAM(_FileInformationData, FileInformationClass, lpFileInformation);
    ADD_IN_PARAM(DWORD, dwBufferSize);

    API_DYN_CALL_T(BOOL, SetFileInformationByHandle,
        hFile,
        FileInformationClass,
        lpFileInformation,
        dwBufferSize);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(SetFileInformationByHandle,
    BOOL (__stdcall *)(
        HANDLE,
        FILE_INFO_BY_HANDLE_CLASS,
        LPVOID,
        DWORD)
)