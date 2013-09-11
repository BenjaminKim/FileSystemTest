#include "stdafx.h"
#include "TestCreateRemoveDirectory.h"
#include "DirectoryManagement/ApiCreateDirectory.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"
#include "FileManagement/ApiDeleteFile.h"
#include "FileManagement/ApiSetFileAttributes.h"
#include "FileManagement/ApiGetFileAttributes.h"

using namespace std;

void Test_CreateAndRemoveDirecotryAll()
{
    Test_CreateDirectory_Basic();
    Test_RemoveDirecotryHavingSomeFiles();
    Test_RemoveReadOnlyDirecotry();
}

/**
@brief CreateDirectory와 RemoveDirectory를 모두 테스트.
*/
void Test_CreateDirectory_Basic()
{
    DEF_TESTLOG_T("Test_CreateDirectory_Basic, 디렉토리 기본 생성, 삭제");

    wstring directoryName = GetTestFileName();

    DWORD dw = apiCreateDirectory(directoryName.c_str(), 0);

    if(dw == 0)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateDirectory Function was failed." << endl;
        return;
    }

    BOOL fSucceed = apiRemoveDirectory(directoryName.c_str());

    if(!fSucceed)
    {
        log.GetStream(TestLog::MT_ERROR) << L"RemoveDirectory Function was failed." << endl;
        return;
    }

    log.Ok();
}

void Test_RemoveDirecotryHavingSomeFiles()
{
    DEF_TESTLOG_T("Test_RemoveDirecotryHavingSomeFiles, 하위에 파일이 존재하는 디렉토리를 삭제");

    wstring directoryName = GetTestFileName(L"Test_RemoveDirecotryHavingSomeFiles");

    DWORD dw = apiCreateDirectory(directoryName.c_str(), 0);

    if(dw == 0)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateDirectory Function was failed." << endl;
        return;
    }

    TouchFile(log, directoryName + L"\\" + GetTestFileName(L"testfile.txt"));

    BOOL fSucceed = apiRemoveDirectory(directoryName.c_str());

    if(!fSucceed)
    {
        log.GetStream(TestLog::MT_ERROR) << L"RemoveDirectory Function was failed." << endl;
        
        uDeleteFile((directoryName + L"\\" + GetTestFileName(L"testfile.txt")).c_str());
        uRemoveDirectory(directoryName.c_str());
    }

    log.Ok();
}

void Test_RemoveReadOnlyDirecotry()
{
    DEF_TESTLOG_T("Test_RemoveReadOnlyDirecotry, 읽기 전용 디렉토리 삭제를 시도");

    wstring directoryName = GetTestFileName(L"Test_RemoveReadOnlyDirecotry");

    DWORD dw = uCreateDirectory(directoryName.c_str(), 0);

    if(dw == 0)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateDirectory Function has failed." << endl;
        return;
    }

    BOOL fOk = uSetFileAttributes(directoryName.c_str(), FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_DIRECTORY);
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileAttributes Function has failed." << endl;
    }

    BOOL fSucceed = apiRemoveDirectory(directoryName.c_str());

    if(fSucceed)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Wrong Result. The test case must be failed." << endl;
        return;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"RemoveDirectory Function has failed." << endl;

        uSetFileAttributes(directoryName.c_str(), FILE_ATTRIBUTE_DIRECTORY);
        uRemoveDirectory(directoryName.c_str());
    }

    log.Ok();
}