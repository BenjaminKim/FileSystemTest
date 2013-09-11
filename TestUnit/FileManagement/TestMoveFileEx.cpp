#include "stdafx.h"
#include "TestMoveFileEx.h"
#include "FileManagement/ApiMoveFileEx.h"
#include "../File.h"
#include "FileManagement/ApiCreateFile.h"

using namespace std;

void Test_MoveFileEx_Basic(DWORD dwFlags)
{
    DEF_TESTLOG_T("Test_MoveFileEx_Basic, 여러 dwFlags를 넣어본다.");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL result = apiMoveFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), dwFlags);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveFileEx_NoExistingSrc(DWORD dwFlags)
{
    DEF_TESTLOG_T("Test_MoveFileEx_NoExistingSrc, 존재하지 않는 원본파일에 대해 적용. 여러 dwFlags를 넣어본다.");
    log.GetStream(TestLog::MT_MESSAGE) << L"dwFlags " << apiMoveFileEx.GetString_dwFlags(dwFlags) << endl;;

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(IsFileExist(pSrcFileName))
    {
        if(!uDeleteFile(pSrcFileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"존재하는 Cannot delete the file." << endl;
            return;
        }
    }

    BOOL result = apiMoveFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), dwFlags);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveFileEx_SharingViolationSrcShareMode(DWORD dwShareMode, DWORD dwFlags)
{
    DEF_TESTLOG_T("Test_MoveFileEx_SharingViolationSrc, 원본 파일의 공유권한을 달리해가면서 테스트");
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode) << endl;
    log.GetStream(TestLog::MT_MESSAGE) << L"dwFlags " << apiMoveFileEx.GetString_dwFlags(dwFlags) << endl;

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    {
        File f(pSrcFileName, GENERIC_READ, dwShareMode, OPEN_EXISTING);
        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            return;
        }

        BOOL result = apiMoveFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), dwFlags);

        f.CloseHandle();
        if(result)
        {
            CheckFileData(log, pDstFileName);
        }
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveFileEx_SharingViolationSrc(DWORD dwFlags)
{
    Test_MoveFileEx_SharingViolationSrcShareMode(0, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_WRITE, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, dwFlags);
}

void Test_MoveFileEx_ExistingDst(DWORD dwFlags)
{
    DEF_TESTLOG_T("Test_MoveFileEx_ExistingDst, 이미 존재하는 목적지파일에 대해 적용. 여러 dwFlags를 넣어본다.");
    log.GetStream(TestLog::MT_MESSAGE) << L"dwFlags " << apiMoveFileEx.GetString_dwFlags(dwFlags) << endl;

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    if(!TouchFile(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL result = apiMoveFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), dwFlags);

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveFileEx_ExistingDstSharingViolationShareMode(DWORD dwShareMode, DWORD dwFlags)
{
    DEF_TESTLOG_T("Test_MoveFileEx_ExistingDstSharingViolationShareMode, 목적지 파일의 공유 권한에 대한 테스트");
    log.GetStream(TestLog::MT_MESSAGE) << L"목적지 파일을 특정 공유 모드와 플래그로 열어놓은 채로 원본파일을 목적파일로 이동 테스트" << endl;
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode) << endl;
    log.GetStream(TestLog::MT_MESSAGE) << L"dwFlags " << apiMoveFileEx.GetString_dwFlags(dwFlags) << endl;

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    if(!TouchFile(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    File f(pDstFileName, GENERIC_READ, dwShareMode, OPEN_EXISTING);
    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
        return;
    }

    BOOL result = apiMoveFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), dwFlags);
    f.CloseHandle();

    if(result)
    {
        CheckFileData(log, pDstFileName);
    }    

    if(!DeleteFileOrCheck(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_MoveFileEx_ExistingDstSharingViolation(DWORD dwFlags)
{
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(0, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE, dwFlags);
    Test_MoveFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, dwFlags);
}