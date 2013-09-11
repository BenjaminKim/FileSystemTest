#include "stdafx.h"
#include "TestCopyFile.h"
#include "FileManagement/ApiCopyFile.h"
#include "../File.h"
#include "FileManagement/ApiCreateFile.h"

using namespace std;

void Test_CopyFile_Normal()
{
    DEF_TESTLOG_T("Test_CopyFile_Normal");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    BOOL result = apiCopyFile(pSrcFileName.c_str(), pDstFileName.c_str(), TRUE);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        return;
    }

    log.Ok();
}

void Test_CopyFile_NoExistingSrc()
{
    DEF_TESTLOG_T("Test_CopyFile_NoExistingSrc");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    BOOL result = apiCopyFile(pSrcFileName.c_str(), pDstFileName.c_str(), TRUE);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        return;
    }
    
    log.Ok();
}

void Test_CopyFile_SharingViolationSrcShareMode(DWORD dwShareMode)
{
    DEF_TESTLOG_T("Test_CopyFile_SharingViolationSrc");
    log.GetStream(TestLog::MT_MESSAGE) << L"원본 파일을 특정 공유 모드와 플래그로 열어놓은 채로 복사 테스트" << endl;
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode) << endl;

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    {
        File f(pSrcFileName, GENERIC_READ, dwShareMode, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            return;
        }

        BOOL result = apiCopyFile(pSrcFileName.c_str(), pDstFileName.c_str(), TRUE);

        if(result)
        {
            CheckFileData(log, pDstFileName);
        }

        result = f.CloseHandle();
        if(!result)
        {
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
            return;
        }
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        return;
    }
    
    log.Ok();
}

void Test_CopyFile_SharingViolationSrc()
{
    Test_CopyFile_SharingViolationSrcShareMode(0);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_READ);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_WRITE);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_DELETE);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE);
    Test_CopyFile_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
}

void CopyFile_ExistingDst(TestLog& log, BOOL bFailIfExists)
{
    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    if(!TouchFile(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    BOOL result = apiCopyFile(pSrcFileName.c_str(), pDstFileName.c_str(), bFailIfExists);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        return;
    }

    log.Ok();
}

void Test_CopyFile_ExistingDstFail()
{
    DEF_TESTLOG_T("Test_CopyFile_ExistingDstFail");

    CopyFile_ExistingDst(log, TRUE);

    log.Ok();
}

void Test_CopyFile_ExistingDstNoFail()
{
    DEF_TESTLOG_T("Test_CopyFile_ExistingDstNoFail");

    CopyFile_ExistingDst(log, FALSE);

    log.Ok();
}

void Test_CopyFile_ExistingDstSharingViolationShareMode(DWORD dwShareMode)
{
    DEF_TESTLOG_T("Test_CopyFile_ExistingDstSharingViolationShareMode");
    log.GetStream(TestLog::MT_MESSAGE) << L"목적 파일을 특정 공유 모드로 열어놓은 채로 복사 테스트" << endl;
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode);

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    if(!TouchFile(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << endl;
        return;
    }

    {
        File f(pDstFileName, GENERIC_READ, dwShareMode, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            return;
        }

        BOOL result = apiCopyFile(pSrcFileName.c_str(), pDstFileName.c_str(), FALSE);

        if(result)
        {
            CheckFileData(log, pDstFileName);
        }

        result = f.CloseHandle();
        if(!result)
        {
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
            return;
        }
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"만들어진 파일을 삭제할 수 없습니다." << endl;
        return;
    }

    log.Ok();
}

void Test_CopyFile_ExistingDstSharingViolation()
{
    Test_CopyFile_ExistingDstSharingViolationShareMode(0);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_READ);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_DELETE);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE);
    Test_CopyFile_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
}