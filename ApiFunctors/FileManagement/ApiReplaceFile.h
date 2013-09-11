#pragma once


DEFINE_API_CLASS_BEGIN(ReplaceFile)

static std::wstring GetString_dwReplaceFlags(DWORD dwReplaceFlags)
{
    CHECK_BIT_BEGIN_HEX(dwReplaceFlags)
    
    CHECK_BIT(REPLACEFILE_WRITE_THROUGH)
    CHECK_BIT(REPLACEFILE_IGNORE_MERGE_ERRORS)
    // Supported by Windows Vista or later.
    //CHECK_BIT(REPLACEFILE_IGNORE_ACL_ERRORS)

    CHECK_BIT_END()
}

BOOL operator()(
    __in        LPCTSTR lpReplacedFileName,
    __in        LPCTSTR lpReplacementFileName,
    __in_opt    LPCTSTR lpBackupFileName,
    __in        DWORD dwReplaceFlags,
    __reserved  LPVOID lpExclude,
    __reserved  LPVOID lpReserved)
{
    ADD_IN_PARAM(PSTR, lpReplacedFileName);
    ADD_IN_PARAM(PSTR, lpReplacementFileName);
    ADD_IN_PARAM(PSTR, lpBackupFileName);
    ADD_IN_PARAM(_dwReplaceFlags, dwReplaceFlags);
    ADD_IN_PARAM(PVOID, lpExclude);
    ADD_IN_PARAM(PVOID, lpReserved);

    API_CALL_T(BOOL, ReplaceFile,
        lpReplacedFileName,
        lpReplacementFileName,
        lpBackupFileName,
        dwReplaceFlags,
        lpExclude,
        lpReserved);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()