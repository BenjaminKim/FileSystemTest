#include "stdafx.h"
#include "TestWriteFile.h"
#include "FileIO/ApiWriteFile.h"
#include "../File.h"
#include "FileManagement/ApiGetFileTime.h"
#include "FileManagement/ApiSetFileTime.h"

using namespace std;

void Test_WriteFileAndSetFileTime()
{
    DEF_TESTLOG_T("Test_WriteFileAndSetFileTime, 쓰기 이후 파일시간을 설정");

    wstring fileName = GetTestFileName();
    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성하는데 실패했습니다." << endl;
        return;
    }

    File f(fileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);

    TCHAR buffer[] = L"Test1234567890 Test1234567890 Test1234567890 Test1234567890 Test1234567890\r\n";
    DWORD writeBytes = 0;
    BOOL fOk = apiWriteFile(f, buffer, sizeof(buffer), &writeBytes, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile" << endl;
        return;
    }
    if(writeBytes != sizeof(buffer))
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
        return;
    }

    FILETIME ft1, ft2, ft3;
    ft1.dwHighDateTime = 100000;
    ft1.dwLowDateTime = 1000000;
    if(!apiSetFileTime(f, &ft1, &ft1, &ft1))
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileTime failed." << endl;
        return;
    }

    if(!apiGetFileTime(f, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    f.CloseHandle();
    DeleteFile(fileName.c_str());

    log.Ok();
}

void Test_SetFileTimeAndWriteFile()
{
    DEF_TESTLOG_T("Test_SetFileTimeAndWriteFile, 파일시간을 먼저 설정한 후 파일 쓰고 닫기");

    wstring fileName = GetTestFileName();
    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성하는데 실패했습니다." << endl;
        return;
    }

    File f(fileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);
    File f2(fileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);

    FILETIME ft1, ft2, ft3;
    
    if(!apiGetFileTime(f, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    if(!apiGetFileTime(f2, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    ft1.dwHighDateTime = 100000;
    ft1.dwLowDateTime = 1000000;
    if(!apiSetFileTime(f, &ft1, &ft1, &ft1))
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileTime failed." << endl;
        return;
    }

    TCHAR buffer[] = L"Test1234567890 Test1234567890 Test1234567890 Test1234567890 Test1234567890\r\n";
    DWORD writeBytes = 0;
    BOOL fOk = apiWriteFile(f, buffer, sizeof(buffer), &writeBytes, 0);
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile" << endl;
        return;
    }
    if(writeBytes != sizeof(buffer))
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
        return;
    }

    if(!apiGetFileTime(f, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    fOk = apiWriteFile(f2, buffer, sizeof(buffer), &writeBytes, 0);

    FlushFileBuffers(f);
    FlushFileBuffers(f2);

    if(!apiGetFileTime(f2, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    f.CloseHandle();

    if(!apiGetFileTime(f2, &ft1, &ft2, &ft3))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileTime failed." << endl;
        return;
    }

    f2.CloseHandle();

    DeleteFile(fileName.c_str());

    log.Ok();
}
