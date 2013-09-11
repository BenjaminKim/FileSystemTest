#include "stdafx.h"
#include "TestSetFileTime.h"
#include "FileManagement/ApiSetFileTime.h"
#include "FileManagement/ApiGetFileTime.h"
#include "../Combinator.h"
#include "FileManagement/ApiDeleteFile.h"
#include "DirectoryManagement/ApiCreateDirectory.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"
#include "TestUnit/File.h"

using namespace std;

void Test_SetFileTimeAll()
{
    FILETIME ft1000;
    ft1000.dwHighDateTime = 1000;
    ft1000.dwLowDateTime = 1000;

    FILETIME ft500;
    ft500.dwHighDateTime = 500;
    ft500.dwLowDateTime = 500;

    FILETIME ft300;
    ft300.dwHighDateTime = 300;
    ft300.dwLowDateTime = 300;

    Test_SetFileTime(0,                 0,                  0);
    Test_SetFileTime(0,                 0,                  &ft1000);
    Test_SetFileTime(0,                 &ft500,             0); 
    Test_SetFileTime(0,                 &ft500,             &ft1000);
    Test_SetFileTime(&ft300,            0,                  0);
    Test_SetFileTime(&ft300,            0,                  &ft1000);
    Test_SetFileTime(&ft300,            &ft500,             0);
    Test_SetFileTime(&ft300,            &ft500,             &ft1000);    
}

void Test_SetFileTime(const FILETIME* lpCreationTime,
                      const FILETIME* lpLastAccessTime,
                      const FILETIME* lpLastWriteTime)
{
    DEF_TESTLOG_T("Test_SetFileTime, 파일에 대해 모든 플래그의 조합을 입력해봅니다.");
    std::wstring fileName = GetTestFileName();

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << GetLastErrorStr() << endl;
        return;
    }

    File f(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE);

    log.GetStream(TestLog::MT_ERROR) << L"1" << GetLastErrorStr() << endl;
    BOOL fOk = apiSetFileTime(f, lpCreationTime, lpLastAccessTime, lpLastWriteTime);

    log.GetStream(TestLog::MT_ERROR) << L"2" << GetLastErrorStr() << endl;

    if(fOk)
    {
        FILETIME a, b, c;
        if(!apiGetFileTime(f, &a, &b, &c))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Api가 실패했습니다." << GetLastErrorStr() << endl;
        }
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"Api가 실패했습니다." << GetLastErrorStr() << endl;
    }

    f.CloseHandle();

    if(!DeleteFile(fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제할 수 없습니다." << GetLastErrorStr() << endl;
        return;
    }

    log.Ok();
}