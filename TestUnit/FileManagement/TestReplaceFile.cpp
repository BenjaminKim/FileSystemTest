#include "stdafx.h"
#include "TestReplaceFile.h"
#include "FileManagement/ApiReplaceFile.h"

using namespace std;
void Test_ReplaceFile_All()
{
    Test_ReplaceFile_Basic();
}

/**
@brief 특정 파일(ToBeReplacedFile)을 어떤 한 파일(SourceFile)로 바꿔버린다.
ToBeReplacedFile이 바꿔치기 전의 데이터를 Backup 파일로 보존할 수 있다.
*/
void Test_ReplaceFile_Basic()
{
    DEF_TESTLOG_T("Test_ReplaceFile_Basic, Replace파일의 기본 테스트. 백업 포함.");

    wstring toBeReplaced = GetTestFileName(L"ReplaceFile_toBeReplaced");
    wstring ReplaceSource = GetTestFileName(L"ReplaceFile_Source");
    wstring backupFileName = GetTestFileName(L"ReplaceFile_BackupFile");

    if(!MakeFile(log, ReplaceSource, 500))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    if(!MakeFile(log, toBeReplaced))
    {
        log.GetStream(TestLog::MT_ERROR) << L"" << endl;
        return;
    }

    BOOL fOk = apiReplaceFile(toBeReplaced.c_str(), ReplaceSource.c_str(), backupFileName.c_str(), REPLACEFILE_WRITE_THROUGH, 0, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Replace 파일 함수가 실패했습니다." << endl;
    }

    uDeleteFile(toBeReplaced.c_str());
    uDeleteFile(ReplaceSource.c_str());
    uDeleteFile(backupFileName.c_str());

    log.Ok();
}

void Test_ReplaceFile_NoFileToBeReplaced()
{
    DEF_TESTLOG_T("Test_ReplaceFile_NoFileToBeReplaced, Replace할 파일을 생성하지 않은채로 테스트");

    wstring toBeReplaced = GetTestFileName(L"ReplaceFile_toBeReplaced");
    wstring ReplaceSource = GetTestFileName(L"ReplaceFile_Source");
    wstring backupFileName = GetTestFileName(L"ReplaceFile_BackupFile");

    if(!MakeFile(log, ReplaceSource, 500))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    uDeleteFile(toBeReplaced.c_str());

    //toBeReplaced은 존재하지 않는다.
    BOOL fOk = apiReplaceFile(toBeReplaced.c_str(), ReplaceSource.c_str(), backupFileName.c_str(), REPLACEFILE_WRITE_THROUGH, 0, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Replace 파일 함수가 실패했습니다." << endl;
    }

    uDeleteFile(toBeReplaced.c_str());
    uDeleteFile(ReplaceSource.c_str());
    uDeleteFile(backupFileName.c_str());

    log.Ok();
}