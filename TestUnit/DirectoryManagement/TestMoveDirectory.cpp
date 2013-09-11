#include "stdafx.h"
#include "TestMoveDirectory.h"
#include "FileManagement/ApiMoveFile.h"
#include "../File.h"
#include "FileManagement/ApiCreateFile.h"
#include "FileManagement/ApiDeleteFile.h"
#include "DirectoryManagement/ApiCreateDirectory.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"

using namespace std;

void Test_MoveDirectory_Normal()
{
    DEF_TESTLOG_T("Test_MoveDirectory_Normal, �⺻ ���丮 �̵� �׽�Ʈ");

    const wstring sSrcFileName = GetSrcFileName();
    const wstring sDstFileName = GetDstFileName();

    if(!CreateDirectory(sSrcFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        return;
    }

    BOOL result = apiMoveFile(sSrcFileName.c_str(), sDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮 �̵��� �����߽��ϴ�.." << endl;
    }

    if(uRemoveDirectory(sSrcFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"The source directory is deleted." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"The source directory couldn't be deleted." << endl;
    }

    if(uRemoveDirectory(sDstFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"The destination directory is deleted." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"The destination directory couldn't be deleted." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveDirectory_NoExistingSrc()
{
    DEF_TESTLOG_T("Test_MoveDirectoru_NoExistingSrc, �������� �ʴ� ���丮�� �̵� �õ�");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(IsFileExist(pSrcFileName))
    {
        if(!uRemoveDirectory(pSrcFileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"�����ϴ� ���丮�� ������ �� �����ϴ�." << endl;
            return;
        }
    }

    BOOL result = apiMoveFile(pSrcFileName.c_str(), pDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮 �̵��� �����߽��ϴ�.." << endl;
    }

    if(!uRemoveDirectory(pSrcFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"������� ���丮�� ������ �� �����ϴ�." << endl;
    }
    if(!uRemoveDirectory(pDstFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"������� ���丮�� ������ �� �����ϴ�." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveDirectory_ExistingDst()
{
    DEF_TESTLOG_T("Test_MoveDirectory_ExistingDst, �����ϴ� ���� ���丮�� ���� ���");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!uCreateDirectory(pSrcFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        return;
    }

    if(!uCreateDirectory(pDstFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        return;
    }

    BOOL result = apiMoveFile(pSrcFileName.c_str(), pDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮 �̵��� �����߽��ϴ�.." << endl;
    }

    if(!uRemoveDirectory(pSrcFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"������� ���丮�� ������ �� �����ϴ�." << endl;
    }
    if(!uRemoveDirectory(pDstFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"������� ���丮�� ������ �� �����ϴ�." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveDirirectory_WithOpenedSubFiles()
{
    DEF_TESTLOG_T("Test_MoveDirectory_WithOpenedSubFiles, ������ ������ �����ؼ� �������ä ���丮�� �̵�");

    wstring dirName = GetTestFileName(L"Test_MoveDirectory_WithOpenedSubFiles");

    BOOL fOk = uCreateDirectory(dirName.c_str(), 0);
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"The directory couldn't be created." << endl;
        return;
    }

    wstring fileName = GetTestFileName(L"Test_MoveDirectory_WithOpenedSubFiles.txt");

    File f1(dirName + L"\\" + fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);
    if(!f1.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"������ �� �� �����ϴ�." << endl;
        return;
    }

    fOk = apiMoveFile(dirName.c_str(), (L"MOVED_" + dirName).c_str());

    f1.CloseHandle();

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮 �̸��� ������ �� �����ϴ�." << endl;
        if(!uDeleteFile((dirName + L"\\" + fileName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"������ ������ �� �����ϴ�." << endl;
        }

        if(!uRemoveDirectory(dirName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        }
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"---Wrong Result---. The test case must be failed." << endl;

        // but try to clean up.
        if(!uDeleteFile((L"MOVED_" + dirName + L"\\" + fileName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"������ ������ �� �����ϴ�." << endl;
        }

        if(!uRemoveDirectory((L"MOVED_" + dirName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        }
    }


    log.Ok();
}

void Test_MoveDirectory_WithSubFiles()
{
    DEF_TESTLOG_T("Test_MoveDir_AsOpendSubFiles, ���� ���ϵ���(�������� ����) ������ �ִ� ���丮�� �̵�");

    wstring dirName = GetTestFileName(L"Test_MoveDirectory_WithSubFiles");

    BOOL fOk = uCreateDirectory(dirName.c_str(), 0);

    wstring fileName1 = GetTestFileName(L"Test_MoveDirectory_WithSubFiles1.txt");
    wstring fileName2 = GetTestFileName(L"Test_MoveDirectory_WithSubFiles2.txt");

    bool ok = TouchFile(log, dirName + L"\\" + fileName1);
    if(ok == false)
    {
        uRemoveDirectory(dirName.c_str());
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file1." << endl;
        return;
    }

    ok = TouchFile(log, dirName + L"\\" + fileName2);
    if(ok == false)
    {
        uDeleteFile((dirName + L"\\" + fileName1).c_str());
        uRemoveDirectory(dirName.c_str());
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file2." << endl;
        return;
    }
        
    fOk = apiMoveFile(dirName.c_str(), (L"MOVED_" + dirName).c_str());
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���丮 �̸��� ������ �� �����ϴ�." << endl;

        if(!uDeleteFile((dirName + L"\\" + fileName1).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file1." << endl;
        }
        if(!uDeleteFile((dirName + L"\\" + fileName2).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file2." << endl;
        }

        if(!uRemoveDirectory(dirName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"���丮�� ������ �� �����ϴ�." << endl;
        }
    }
    else
    {
        uDeleteFile((L"MOVED_" + dirName + L"\\" + fileName1).c_str());
        uDeleteFile((L"MOVED_" + dirName + L"\\" + fileName2).c_str());
        uRemoveDirectory((L"MOVED_" + dirName).c_str());
        log.GetStream(TestLog::MT_ERROR) << L"Wrong Result. The test case must be failed." << endl;
    }

    log.Ok();
}

void Test_MoveDirectory_WithSubFilesOpened()
{
}