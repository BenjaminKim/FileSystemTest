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
    DEF_TESTLOG_T("Test_MoveDirectory_Normal, 기본 디렉토리 이동 테스트");

    const wstring sSrcFileName = GetSrcFileName();
    const wstring sDstFileName = GetDstFileName();

    if(!CreateDirectory(sSrcFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 생성할 수 없습니다." << endl;
        return;
    }

    BOOL result = apiMoveFile(sSrcFileName.c_str(), sDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 이동이 실패했습니다.." << endl;
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
    DEF_TESTLOG_T("Test_MoveDirectoru_NoExistingSrc, 존재하지 않는 디렉토리를 이동 시도");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(IsFileExist(pSrcFileName))
    {
        if(!uRemoveDirectory(pSrcFileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"존재하는 디렉토리를 삭제할 수 없습니다." << endl;
            return;
        }
    }

    BOOL result = apiMoveFile(pSrcFileName.c_str(), pDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 이동이 실패했습니다.." << endl;
    }

    if(!uRemoveDirectory(pSrcFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 디렉토리를 삭제할 수 없습니다." << endl;
    }
    if(!uRemoveDirectory(pDstFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 디렉토리를 삭제할 수 없습니다." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveDirectory_ExistingDst()
{
    DEF_TESTLOG_T("Test_MoveDirectory_ExistingDst, 존재하는 목적 디렉토리가 있을 경우");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!uCreateDirectory(pSrcFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 생성할 수 없습니다." << endl;
        return;
    }

    if(!uCreateDirectory(pDstFileName.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 생성할 수 없습니다." << endl;
        return;
    }

    BOOL result = apiMoveFile(pSrcFileName.c_str(), pDstFileName.c_str());

    if(!result)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 이동이 실패했습니다.." << endl;
    }

    if(!uRemoveDirectory(pSrcFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 디렉토리를 삭제할 수 없습니다." << endl;
    }
    if(!uRemoveDirectory(pDstFileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 디렉토리를 삭제할 수 없습니다." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveDirirectory_WithOpenedSubFiles()
{
    DEF_TESTLOG_T("Test_MoveDirectory_WithOpenedSubFiles, 하위에 파일을 생성해서 열어놓은채 디렉토리를 이동");

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
        log.GetStream(TestLog::MT_ERROR) << L"파일을 열 수 없습니다." << endl;
        return;
    }

    fOk = apiMoveFile(dirName.c_str(), (L"MOVED_" + dirName).c_str());

    f1.CloseHandle();

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 이름을 변경할 수 없습니다." << endl;
        if(!uDeleteFile((dirName + L"\\" + fileName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제할 수 없습니다." << endl;
        }

        if(!uRemoveDirectory(dirName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 삭제할 수 없습니다." << endl;
        }
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"---Wrong Result---. The test case must be failed." << endl;

        // but try to clean up.
        if(!uDeleteFile((L"MOVED_" + dirName + L"\\" + fileName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제할 수 없습니다." << endl;
        }

        if(!uRemoveDirectory((L"MOVED_" + dirName).c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 삭제할 수 없습니다." << endl;
        }
    }


    log.Ok();
}

void Test_MoveDirectory_WithSubFiles()
{
    DEF_TESTLOG_T("Test_MoveDir_AsOpendSubFiles, 하위 파일들을(열려있지 않은) 가지고 있는 디렉토리를 이동");

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
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 이름을 변경할 수 없습니다." << endl;

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
            log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 삭제할 수 없습니다." << endl;
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