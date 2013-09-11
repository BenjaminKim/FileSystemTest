#pragma once


DEFINE_API_CLASS_BEGIN(CopyFileEx)

static std::wstring GetString_dwCopyFlags(DWORD dwCopyFlags)
{
    CHECK_BIT_BEGIN_HEX(dwCopyFlags)

    CHECK_BIT(COPY_FILE_ALLOW_DECRYPTED_DESTINATION)
    CHECK_BIT(COPY_FILE_COPY_SYMLINK)
    CHECK_BIT(COPY_FILE_FAIL_IF_EXISTS)
    CHECK_BIT(COPY_FILE_OPEN_SOURCE_FOR_WRITE)
    CHECK_BIT(COPY_FILE_RESTARTABLE)

    CHECK_BIT_END()
}

BOOL operator()(
    __in      LPCTSTR lpExistingFileName,
    __in      LPCTSTR lpNewFileName,
    __in_opt  LPPROGRESS_ROUTINE lpProgressRoutine,
    __in_opt  LPVOID lpData,
    __in_opt  LPBOOL pbCancel,
    __in      DWORD dwCopyFlags)
{
    ADD_IN_PARAM(PSTR, lpExistingFileName);
    ADD_IN_PARAM(PSTR, lpNewFileName);
    ADD_IN_PARAM(PVOID, lpProgressRoutine);
    ADD_IN_PARAM(PVOID, lpData);
    ADD_IN_PARAM(PBOOL, pbCancel);
    ADD_IN_PARAM(_dwCopyFlags, dwCopyFlags);

    API_CALL_T(BOOL, CopyFileEx,
        lpExistingFileName,
        lpNewFileName,
        lpProgressRoutine,
        lpData,
        pbCancel,
        dwCopyFlags);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()