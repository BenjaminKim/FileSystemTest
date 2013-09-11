#pragma once


DEFINE_API_CLASS_BEGIN(CreateFile)

static std::wstring GetString_dwDesiredAccess(DWORD dwDesiredAccess)
{
    CHECK_BIT_BEGIN_HEX(dwDesiredAccess)

    // GENERIC
    CHECK_BIT_CLEAR(GENERIC_ALL)
    CHECK_BIT_CLEAR(GENERIC_EXECUTE)
    CHECK_BIT_CLEAR(GENERIC_READ)
    CHECK_BIT_CLEAR(GENERIC_WRITE)

    // FILE_GENERIC
    DWORD fileGenericMask = 0;
    if((x & FILE_GENERIC_READ) == FILE_GENERIC_READ)
    {
        oss << L"FILE_GENERIC_READ, ";
        x |= FILE_GENERIC_READ;
    }
    if((x & FILE_GENERIC_WRITE) == FILE_GENERIC_WRITE)
    {
        oss << L"FILE_GENERIC_WRITE, ";
        x |= FILE_GENERIC_WRITE;
    }
    if((x & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE)
    {
        oss << L"FILE_GENERIC_EXECUTE, ";
        x |= FILE_GENERIC_EXECUTE;
    }
    x &= ~fileGenericMask;

    // object specific
    CHECK_BIT(FILE_READ_DATA)
    CHECK_BIT(FILE_WRITE_DATA)
    CHECK_BIT(FILE_APPEND_DATA)
    CHECK_BIT(FILE_READ_EA)
    CHECK_BIT(FILE_WRITE_EA)
    CHECK_BIT(FILE_EXECUTE)
    CHECK_BIT(FILE_DELETE_CHILD)
    CHECK_BIT(FILE_READ_ATTRIBUTES)
    CHECK_BIT(FILE_WRITE_ATTRIBUTES)

    CHECK_BIT_END()
}

static std::wstring GetString_dwShareMode(DWORD dwShareMode)
{
    CHECK_BIT_BEGIN_HEX(dwShareMode)

    CHECK_BIT(FILE_SHARE_READ)
    CHECK_BIT(FILE_SHARE_WRITE)
    CHECK_BIT(FILE_SHARE_DELETE)

    CHECK_BIT_END()
}

static std::wstring GetString_dwCreationDisposition(DWORD dwCreationDisposition)
{
    SWITCH_BEGIN(dwCreationDisposition)
        CASE(CREATE_NEW)
        CASE(CREATE_ALWAYS)
        CASE(OPEN_EXISTING)
        CASE(OPEN_ALWAYS)
        CASE(TRUNCATE_EXISTING)
    SWITCH_END()
}

static std::wstring GetString_dwFlagsAndAttributes(DWORD dwFlagsAndAttributes)
{
    CHECK_BIT_BEGIN_HEX(dwFlagsAndAttributes)

    CHECK_BIT(FILE_ATTRIBUTE_READONLY)
    CHECK_BIT(FILE_ATTRIBUTE_HIDDEN)
    CHECK_BIT(FILE_ATTRIBUTE_SYSTEM)
    CHECK_BIT(FILE_ATTRIBUTE_DIRECTORY)
    CHECK_BIT(FILE_ATTRIBUTE_ARCHIVE)
    CHECK_BIT(FILE_ATTRIBUTE_DEVICE)
    CHECK_BIT(FILE_ATTRIBUTE_NORMAL)
    CHECK_BIT(FILE_ATTRIBUTE_TEMPORARY)
    CHECK_BIT(FILE_ATTRIBUTE_SPARSE_FILE)
    CHECK_BIT(FILE_ATTRIBUTE_REPARSE_POINT)
    CHECK_BIT(FILE_ATTRIBUTE_COMPRESSED)
    CHECK_BIT(FILE_ATTRIBUTE_OFFLINE)
    CHECK_BIT(FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)
    CHECK_BIT(FILE_ATTRIBUTE_ENCRYPTED)
    CHECK_BIT(FILE_ATTRIBUTE_VIRTUAL)

    CHECK_BIT(FILE_FLAG_WRITE_THROUGH)
    CHECK_BIT(FILE_FLAG_OVERLAPPED)
    CHECK_BIT(FILE_FLAG_NO_BUFFERING)
    CHECK_BIT(FILE_FLAG_RANDOM_ACCESS)
    CHECK_BIT(FILE_FLAG_SEQUENTIAL_SCAN)
    CHECK_BIT(FILE_FLAG_DELETE_ON_CLOSE)
    CHECK_BIT(FILE_FLAG_BACKUP_SEMANTICS)
    CHECK_BIT(FILE_FLAG_POSIX_SEMANTICS)
    CHECK_BIT(FILE_FLAG_OPEN_REPARSE_POINT)
    CHECK_BIT(FILE_FLAG_OPEN_NO_RECALL)
    CHECK_BIT(FILE_FLAG_FIRST_PIPE_INSTANCE)

    CHECK_BIT_END()
}

HANDLE operator()(
    __in     LPCWSTR lpFileName,
    __in     DWORD dwDesiredAccess,
    __in     DWORD dwShareMode,
    __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in     DWORD dwCreationDisposition,
    __in     DWORD dwFlagsAndAttributes,
    __in_opt HANDLE hTemplateFile)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(_dwDesiredAccess, dwDesiredAccess);
    ADD_IN_PARAM(_dwShareMode, dwShareMode);
    ADD_IN_PARAM(PVOID, lpSecurityAttributes);
    ADD_IN_PARAM(_dwCreationDisposition, dwCreationDisposition);
    ADD_IN_PARAM(_dwFlagsAndAttributes, dwFlagsAndAttributes);
    ADD_IN_PARAM(HANDLE, hTemplateFile);

    API_CALL_T(HANDLE, CreateFileW,
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()