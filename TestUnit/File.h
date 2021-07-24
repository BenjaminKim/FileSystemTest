#pragma once

#include "FileManagement/ApiCreateFile.h"
#include "FileManagement/ApiCloseHandle.h"

class File
{
public:
    File(const std::wstring& filepath) : filepath_(filepath)
    {
        h_ = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, OPEN_EXISTING);
    }

    File(
        __in const std::wstring& filepath,
        __in DWORD dwShareMode) : filepath_(filepath)
    {
        h_ = CreateFile(filepath, GENERIC_READ, dwShareMode, OPEN_EXISTING);
    }

    File(
        __in const std::wstring& filepath,
        __in DWORD dwDesiredAccess,
        __in DWORD dwShareMode) : filepath_(filepath)
    {
        h_ = CreateFile(filepath, dwDesiredAccess, dwShareMode, OPEN_EXISTING);
    }

    File(
        __in const std::wstring& filepath,
        __in DWORD dwDesiredAccess,
        __in DWORD dwShareMode,
        __in DWORD dwCreationDisposition) : filepath_(filepath)
    {
        h_ = CreateFile(filepath, dwDesiredAccess, dwShareMode, dwCreationDisposition);
    }

    ~File()
    {
        CloseHandle();
    }

    operator HANDLE() const
    {
        return h_;
    }

    bool IsValidHandle() const
    {
        return (INVALID_HANDLE_VALUE != h_);
    }

    BOOL CloseHandle()
    {
        if(h_ != INVALID_HANDLE_VALUE)
        {
            BOOL r = uCloseHandle(h_);
            h_ = INVALID_HANDLE_VALUE;
            return r;
        }

        return TRUE;
    }

    BOOL Create()
    {
        if(!IsValidHandle())
        {
            CreateFile(filepath_, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);
        }
    }

private:
    HANDLE h_;
    std::wstring filepath_;

    HANDLE CreateFile(
        __in const std::wstring& filename,
        __in DWORD dwDesiredAccess,
        __in DWORD dwShareMode,
        __in DWORD dwCreationDisposition
        )
    { return uCreateFile(filename.c_str(), dwDesiredAccess, dwShareMode, 0, dwCreationDisposition, 0, 0); }
};
