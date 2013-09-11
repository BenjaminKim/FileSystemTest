#include "stdafx.h"
#include "TestReplaceFile.h"
#include "FileManagement/ApiReplaceFile.h"

using namespace std;
void Test_ReplaceFile_All()
{
    Test_ReplaceFile_Basic();
}

/**
@brief Ư�� ����(ToBeReplacedFile)�� � �� ����(SourceFile)�� �ٲ������.
ToBeReplacedFile�� �ٲ�ġ�� ���� �����͸� Backup ���Ϸ� ������ �� �ִ�.
*/
void Test_ReplaceFile_Basic()
{
    DEF_TESTLOG_T("Test_ReplaceFile_Basic, Replace������ �⺻ �׽�Ʈ. ��� ����.");

    wstring toBeReplaced = GetTestFileName(L"ReplaceFile_toBeReplaced");
    wstring ReplaceSource = GetTestFileName(L"ReplaceFile_Source");
    wstring backupFileName = GetTestFileName(L"ReplaceFile_BackupFile");

    if(!MakeFile(log, ReplaceSource, 500))
    {
        log.GetStream(TestLog::MT_ERROR) << L"���� ������ �����߽��ϴ�." << endl;
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
        log.GetStream(TestLog::MT_ERROR) << L"Replace ���� �Լ��� �����߽��ϴ�." << endl;
    }

    uDeleteFile(toBeReplaced.c_str());
    uDeleteFile(ReplaceSource.c_str());
    uDeleteFile(backupFileName.c_str());

    log.Ok();
}

void Test_ReplaceFile_NoFileToBeReplaced()
{
    DEF_TESTLOG_T("Test_ReplaceFile_NoFileToBeReplaced, Replace�� ������ �������� ����ä�� �׽�Ʈ");

    wstring toBeReplaced = GetTestFileName(L"ReplaceFile_toBeReplaced");
    wstring ReplaceSource = GetTestFileName(L"ReplaceFile_Source");
    wstring backupFileName = GetTestFileName(L"ReplaceFile_BackupFile");

    if(!MakeFile(log, ReplaceSource, 500))
    {
        log.GetStream(TestLog::MT_ERROR) << L"���� ������ �����߽��ϴ�." << endl;
        return;
    }

    uDeleteFile(toBeReplaced.c_str());

    //toBeReplaced�� �������� �ʴ´�.
    BOOL fOk = apiReplaceFile(toBeReplaced.c_str(), ReplaceSource.c_str(), backupFileName.c_str(), REPLACEFILE_WRITE_THROUGH, 0, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Replace ���� �Լ��� �����߽��ϴ�." << endl;
    }

    uDeleteFile(toBeReplaced.c_str());
    uDeleteFile(ReplaceSource.c_str());
    uDeleteFile(backupFileName.c_str());

    log.Ok();
}