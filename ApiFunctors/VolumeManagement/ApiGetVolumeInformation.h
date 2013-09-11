#pragma once


DEFINE_API_CLASS_BEGIN(GetVolumeInformation)

static std::wstring GetString_lpFileSystemFlags(PDWORD lpFileSystemFlags)
{
    if(lpFileSystemFlags)
    {
        CHECK_BIT_BEGIN_HEX(*lpFileSystemFlags)
            
        CHECK_BIT(FILE_CASE_SENSITIVE_SEARCH)
        CHECK_BIT(FILE_CASE_PRESERVED_NAMES)
        CHECK_BIT(FILE_UNICODE_ON_DISK)
        CHECK_BIT(FILE_PERSISTENT_ACLS)
        CHECK_BIT(FILE_FILE_COMPRESSION)
        CHECK_BIT(FILE_VOLUME_QUOTAS)
        CHECK_BIT(FILE_SUPPORTS_SPARSE_FILES)
        CHECK_BIT(FILE_SUPPORTS_REPARSE_POINTS)
        CHECK_BIT(FILE_SUPPORTS_REMOTE_STORAGE)
        CHECK_BIT(FILE_VOLUME_IS_COMPRESSED)
        CHECK_BIT(FILE_SUPPORTS_OBJECT_IDS)
        CHECK_BIT(FILE_SUPPORTS_ENCRYPTION)
        CHECK_BIT(FILE_NAMED_STREAMS)
        CHECK_BIT(FILE_READ_ONLY_VOLUME)
        CHECK_BIT(FILE_SEQUENTIAL_WRITE_ONCE)
        CHECK_BIT(FILE_SUPPORTS_TRANSACTIONS)

        CHECK_BIT_END()
    }
    else
    {
        return L"(NULL)";
    }
}

BOOL operator()(
    __in_opt  LPCWSTR lpRootPathName,
    __out_ecount_opt(nVolumeNameSize) LPWSTR lpVolumeNameBuffer,
    __in      DWORD nVolumeNameSize,
    __out_opt LPDWORD lpVolumeSerialNumber,
    __out_opt LPDWORD lpMaximumComponentLength,
    __out_opt LPDWORD lpFileSystemFlags,
    __out_ecount_opt(nFileSystemNameSize) LPWSTR lpFileSystemNameBuffer,
    __in      DWORD nFileSystemNameSize)
{
    ADD_IN_PARAM(PSTR, lpRootPathName);
    ADD_IN_PARAM(DWORD, nVolumeNameSize);
    ADD_IN_PARAM(DWORD, nFileSystemNameSize);

    API_CALL_T(BOOL, GetVolumeInformationW,
        lpRootPathName,
        lpVolumeNameBuffer,
        nVolumeNameSize,
        lpVolumeSerialNumber,
        lpMaximumComponentLength,
        lpFileSystemFlags,
        lpFileSystemNameBuffer,
        nFileSystemNameSize);

    ADD_OUT_PARAM(PSTR, lpVolumeNameBuffer);
    ADD_OUT_PARAM(PDWORD, lpVolumeSerialNumber);
    ADD_OUT_PARAM(PDWORD, lpMaximumComponentLength);
    ADD_OUT_PARAM(_lpFileSystemFlags, lpFileSystemFlags);
    ADD_OUT_PARAM(PSTR, lpFileSystemNameBuffer);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()