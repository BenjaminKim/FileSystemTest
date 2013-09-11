#include "stdafx.h"
#include "TestSetEndOfFile.h"
#include "FileIO/ApiSetEndOfFile.h"
#include "../File.h"
#include "FileIo/ApiSetFilePointerEx.h"
#include "FileManagement/ApiDeleteFile.h"
#include "FileManagement/ApiGetFileSizeEx.h"

using namespace std;
void Test_SetEndOfFile(const LONGLONG& jQuadPart, DWORD dwMoveMethod);
void Test_SetEndOfFileAndGetFileSize(const LONGLONG& jQuadPart, DWORD dwMoveMethod);


void Test_SetEndOfFile(const LONGLONG& jQuadPart, DWORD dwMoveMethod)
{
    DEF_TESTLOG_T("Test_SetEndOfFile : 파일크기를 확장 ");

    wstring fileName = GetTestFileName();
    BOOL fOk = MakeFile(log, fileName);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
    }

    {
        File f(fileName, GENERIC_WRITE, 0, CREATE_ALWAYS);

        LARGE_INTEGER li;
        li.QuadPart = jQuadPart;
        fOk = apiSetFilePointerEx(f, li, 0, dwMoveMethod);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetFilePointerEx Failed." << endl;
        }

        fOk = apiSetEndOfFile(f);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetEndOfFile Failed." << endl;
        }
    }

    fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }

    log.Ok();
}

void Test_SetEndOfFile_All()
{
    Test_SetEndOfFile(50000, FILE_END);
    Test_SetEndOfFile(1024i64*1024i64*1024i64*4i64 + 1, FILE_END);
    Test_SetEndOfFile(1024i64*1024i64*1024i64*4i64 + 1, FILE_BEGIN);
    Test_SetEndOfFile(1024i64*1024i64*1024i64*4i64 + 1, FILE_CURRENT);

    Test_SetEndOfFileAndGetFileSize(50000, FILE_END);
    Test_SetEndOfFileAndGetFileSize(1024i64*1024i64*1024i64*4i64 + 1, FILE_END);
    Test_SetEndOfFileAndGetFileSize(1024i64*1024i64*1024i64*4i64 + 1, FILE_BEGIN);
    Test_SetEndOfFileAndGetFileSize(1024i64*1024i64*1024i64*4i64 + 1, FILE_CURRENT);
}

void Test_SetEndOfFileAndGetFileSize(const LONGLONG& jQuadPart, DWORD dwMoveMethod)
{
    DEF_TESTLOG_T("Test_SetEndOfFileAndGetFileSize : 파일크기를 확장 ");

    wstring fileName = GetTestFileName();
    BOOL fOk = MakeFile(log, fileName);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
    }

    {
        File f(fileName, GENERIC_WRITE, 0, CREATE_ALWAYS);

        LARGE_INTEGER li;
        li.QuadPart = jQuadPart;
        fOk = apiSetFilePointerEx(f, li, 0, dwMoveMethod);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetFilePointerEx Failed." << endl;
        }

        fOk = apiSetEndOfFile(f);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetEndOfFile Failed." << endl;
        }

        apiGetFileSizeEx(f, &li);
    }

    Sleep(5000); // 캐시 제거

    File f2(fileName); // 서버로 가는지 확인해야 한다.
    LARGE_INTEGER li2;
    apiGetFileSizeEx(f2, &li2);
    f2.CloseHandle();
    
    fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }

    log.Ok();
}

void Test_SetEndOfFileAndGetFileSize2()
{
    DEF_TESTLOG_T("Test_SetEndOfFileAndGetFileSize2 : 파일크기를 확장 ");

    wstring fileName = GetTestFileName();
    BOOL fOk = MakeFile(log, fileName);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
    }

    File f2(fileName, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, OPEN_EXISTING);

    {
        File f(fileName, GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE, OPEN_EXISTING);

        LARGE_INTEGER li;
        li.QuadPart = 1*1024*1024*1024;
        fOk = apiSetFilePointerEx(f, li, 0, FILE_END);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetFilePointerEx Failed." << endl;
        }

        fOk = apiSetEndOfFile(f);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetEndOfFile Failed." << endl;
        }

        apiGetFileSizeEx(f, &li);
    }

    Sleep(5000); // 캐시 제거

    // 서버로 가는지 확인해야 한다.
    LARGE_INTEGER li2;
    apiGetFileSizeEx(f2, &li2);
    f2.CloseHandle();

    apiGetFileSizeEx(f2, &li2);

    fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }

    log.Ok();
}