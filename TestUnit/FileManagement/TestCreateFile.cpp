#include "stdafx.h"
#include "TestCreateFile.h"
#include "FileManagement/ApiCreateFile.h"
#include "../File.h"
#include "FileManagement/ApiGetFileAttributes.h"

using namespace std;

bool Sub_CreateFile_AccessDisposition(TestLog& log, LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwCreationDisposition)
{
    HANDLE h = apiCreateFile(lpFileName,
        dwDesiredAccess,
        FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
        0,
        dwCreationDisposition,
        0,
        0);

    if(h == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
        return false;
    }

    BOOL result = CloseHandle(h);
    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
        return false;
    }

    return true;
}

void Test_CreateFile_NewFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition)
{
    DEF_TESTLOG_T("Calling CreateFile with dwDesiredAccess, dwCreateDisposition.");

    wstring fileName = GetTestFileName();

    BOOL result = Sub_CreateFile_AccessDisposition(log, fileName.c_str(), dwDesiredAccess, dwCreateDisposition);

    if(!DeleteFileOrCheck(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Sub_CreateFile_Disposition" << endl;
        return;
    }

    log.Ok();
}

void Test_CreateFile_NewFileAccessAllDisposition(DWORD dwDesiredAccess)
{
    Test_CreateFile_NewFile(dwDesiredAccess, CREATE_ALWAYS);
    Test_CreateFile_NewFile(dwDesiredAccess, CREATE_NEW);
    Test_CreateFile_NewFile(dwDesiredAccess, OPEN_ALWAYS);
    Test_CreateFile_NewFile(dwDesiredAccess, OPEN_EXISTING);
    Test_CreateFile_NewFile(dwDesiredAccess, TRUNCATE_EXISTING);
}

/**
@brief Cases creating a new file
- GENERIC_READ
- GENERIC_WRITE
- GENERIC_EXECUTE
- GENERIC_ALL
- FILE_GENERIC_READ
- FILE_GENERIC_WRITE
- FILE_GENERIC_EXECUTE

- CREATE_ALWAYS
- CREATE_NEW
- OPEN_ALWAYS
- OPEN_EXISTING
- TRUNCATE_EXISTING
*/
void Test_CreateFile_NewFileAccessDisposition()
{
    Test_CreateFile_NewFileAccessAllDisposition(GENERIC_READ);
    Test_CreateFile_NewFileAccessAllDisposition(GENERIC_WRITE);
    Test_CreateFile_NewFileAccessAllDisposition(GENERIC_EXECUTE);
    Test_CreateFile_NewFileAccessAllDisposition(GENERIC_ALL);

    Test_CreateFile_NewFileAccessAllDisposition(FILE_GENERIC_READ);
    Test_CreateFile_NewFileAccessAllDisposition(FILE_GENERIC_WRITE);
    Test_CreateFile_NewFileAccessAllDisposition(FILE_GENERIC_EXECUTE);
}

void Test_CreateFile_ExistingFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition)
{
    DEF_TESTLOG_T("CreateFile, Calling CreateFile with dwDesiredAccess, dwCreateDisposition when a file already exist.");

    std::wstring fileName = GetTestFileName();

    if(!TouchFile(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL result = Sub_CreateFile_AccessDisposition(log, fileName.c_str(), dwDesiredAccess, dwCreateDisposition);

    // clean up
    if(!DeleteFileOrCheck(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Sub_CreateFile_Disposition" << endl;
        return;
    }

    log.Ok();
}

void Test_CreateFile_ExistingFileAccessAllDisposition(DWORD dwDesiredAccess)
{
    Test_CreateFile_ExistingFile(dwDesiredAccess, CREATE_ALWAYS);
    Test_CreateFile_ExistingFile(dwDesiredAccess, CREATE_NEW);
    Test_CreateFile_ExistingFile(dwDesiredAccess, OPEN_ALWAYS);
    Test_CreateFile_ExistingFile(dwDesiredAccess, OPEN_EXISTING);
    Test_CreateFile_ExistingFile(dwDesiredAccess, TRUNCATE_EXISTING);
}

/**
@brief Cases calling CreateFile when the file already exist.
- GENERIC_READ
- GENERIC_WRITE
- GENERIC_EXECUTE
- GENERIC_ALL
- FILE_GENERIC_READ
- FILE_GENERIC_WRITE
- FILE_GENERIC_EXECUTE

- CREATE_ALWAYS
- CREATE_NEW
- OPEN_ALWAYS
- OPEN_EXISTING
- TRUNCATE_EXISTING
*/
void Test_CreateFile_ExistingFileAccessDisposition()
{
    Test_CreateFile_ExistingFileAccessAllDisposition(GENERIC_READ);
    Test_CreateFile_ExistingFileAccessAllDisposition(GENERIC_WRITE);
    Test_CreateFile_ExistingFileAccessAllDisposition(GENERIC_EXECUTE);
    Test_CreateFile_ExistingFileAccessAllDisposition(GENERIC_ALL);

    Test_CreateFile_ExistingFileAccessAllDisposition(FILE_GENERIC_READ);
    Test_CreateFile_ExistingFileAccessAllDisposition(FILE_GENERIC_WRITE);
    Test_CreateFile_ExistingFileAccessAllDisposition(FILE_GENERIC_EXECUTE);
}

#pragma chMSG(I expected to get DELETE_PENDING but I cant. Why)
void Test_CreateFile_OpenDeletePendingFile()
{
    DEF_TESTLOG_T("Test_CreateFile_OpenDeletePendingFile, Trying to open file which has status DeletePending");

    std::wstring fileName = GetTestFileName(L"Test_CreateFile_OpenDeletePendingFile");

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
            GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        }
        return;
    }

    if(uDeleteFile(fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"The file has been set to DELETE_PENDING status." << GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
    }
    //// delete pending

    File f2(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);
    if(!f2.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to open the file.(Failing is right)" << GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"Wrong Result" << GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
        f2.CloseHandle();
    }

    f.CloseHandle();
    uDeleteFile(fileName.c_str());

    log.Ok();
}

void Test_CreateFile_OpenDirectory()
{
    DEF_TESTLOG_T("Test_CreateFile_OpenDirectory, Trying to open a directory by CreateFile. It should be failed.");

    std::wstring dirName = GetTestFileName(L"Test_CreateFile_OpenDirectory");

    BOOL fOk = CreateDirectory(dirName.c_str(), 0);
    DWORD dwError = GetLastError();

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a directory" << dwError << L"(" << GetErrorDefineString(dwError) << L") " << endl;
        return;
    }

    HANDLE h = CreateFile(dirName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    dwError = GetLastError();
    if(h == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to open the directory. Not error, it should be." << L"(" << GetErrorDefineString(dwError) << L") " << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"Wrong Result." << dwError << L"(" << GetErrorDefineString(dwError) << L") " << endl;
        CloseHandle(h);
    }
    
    fOk = RemoveDirectory(dirName.c_str());
    dwError = GetLastError();
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to delete the directory" << dwError << L"(" << GetErrorDefineString(dwError) << L") " << endl;
        return;
    }

    log.Ok();
}