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

/**
@brief CreateFile, 파일이 없는 상태에서 특정 dwDesiredAccess, dwCreateDisposition 값으로 호출
*/
void Test_CreateFile_NewFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition)
{
    DEF_TESTLOG_T("CreateFile, 파일이 없는 상태에서 특정 dwDesiredAccess, dwCreateDisposition 값으로 호출");

    wstring fileName = GetTestFileName();

    BOOL result = Sub_CreateFile_AccessDisposition(log, fileName.c_str(), dwDesiredAccess, dwCreateDisposition);

    if(!DeleteFileOrCheck(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
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
@brief 파일을 새로 생성하는 경우
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

/**
@brief CreateFile, 파일이 있는 상태에서 특정 dwDesiredAccess, dwCreateDisposition 값으로 호출
*/
void Test_CreateFile_ExistingFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition)
{
    DEF_TESTLOG_T("CreateFile, 파일이 있는 상태에서 특정 dwDesiredAccess, dwCreateDisposition 값으로 호출");

    std::wstring fileName = GetTestFileName();

    if(!TouchFile(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    BOOL result = Sub_CreateFile_AccessDisposition(log, fileName.c_str(), dwDesiredAccess, dwCreateDisposition);

    // 파일 정리
    if(!DeleteFileOrCheck(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
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
@brief 기존 파일이 있을 때, CreateFile을 호출하는 경우
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

#pragma chMSG(여기서 DELETE_PENDING이 안떨어진다. 왜 안되는지 자세히 살펴볼 것)
void Test_CreateFile_OpenDeletePendingFile()
{
    DEF_TESTLOG_T("Test_CreateFile_OpenDeletePendingFile, Delete pending된 상태의 파일을 다른 곳에서 열기 시도");

    std::wstring fileName = GetTestFileName(L"Test_CreateFile_OpenDeletePendingFile");

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
            GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        }
        return;
    }

    if(uDeleteFile(fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"The file has been set delete pending status." << GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
    }
    //// delete pending

    File f2(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);
    if(!f2.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 여는데 실패했습니다. 실패해야 정상이다." << GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L") " << endl;
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
    DEF_TESTLOG_T("Test_CreateFile_OpenDirectory, CreateFile함수로 디렉토리를 열기 시도. 실패해야만 한다.");

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
        log.GetStream(TestLog::MT_ERROR) << L"Failed to open the directory. 정상적인 결과" << L"(" << GetErrorDefineString(dwError) << L") " << endl;
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