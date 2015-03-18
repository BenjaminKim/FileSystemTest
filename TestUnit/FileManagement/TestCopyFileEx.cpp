#include "stdafx.h"
#include "TestCopyFileEx.h"
#include "FileManagement/ApiCopyFileEx.h"
#include "../File.h"

using namespace std;

void Test_CopyFileEx_Normal()
{
    DEF_TESTLOG_T("Test_CopyFileEx_Normal");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), 0, 0, 0, COPY_FILE_FAIL_IF_EXISTS);

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

/**
- If data is transfered half, then cancel the transfering.
When you call CopyFileEx, you should put pbCancel to lpData.
*/
DWORD WINAPI CopyFileCallBack(
    __in     LARGE_INTEGER TotalFileSize,
    __in     LARGE_INTEGER TotalBytesTransferred,
    __in     LARGE_INTEGER /*StreamSize*/,
    __in     LARGE_INTEGER /*StreamBytesTransferred*/,
    __in     DWORD /*dwStreamNumber*/,
    __in     DWORD /*dwCallbackReason*/,
    __in     HANDLE /*hSourceFile*/,
    __in     HANDLE /*hDestinationFile*/,
    __in_opt LPVOID lpData
    )
{
    INT64 jTotalFileSize = TotalFileSize.HighPart;
    jTotalFileSize <<= 32;
    jTotalFileSize += TotalFileSize.LowPart;

    INT64 jTotalBytesTransferred = TotalBytesTransferred.HighPart;
    jTotalBytesTransferred <<= 32;
    jTotalBytesTransferred += TotalBytesTransferred.LowPart;

    if(jTotalBytesTransferred > jTotalFileSize / 2)
    {
        PBOOL pbStopCopy = (PBOOL)lpData;
        if(pbStopCopy)
        {
            *pbStopCopy = TRUE;
        }
    }

    return 0;
}

/**
Canceling test copying file.
*/
void Test_CopyFileEx_Cancle()
{
    DEF_TESTLOG_T("Test_CopyFileEx_Cancle");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    if(!MakeFile(log, pSrcFileName, 20000))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL bCancel = FALSE;
    BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), CopyFileCallBack, &bCancel, &bCancel, COPY_FILE_FAIL_IF_EXISTS);

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

void Test_CopyFileEx_NoExistingSrc()
{
    DEF_TESTLOG_T("Test_CopyFileEx_NoExistingSrc");

    const wstring pSrcFileName = GetSrcFileName();
    const wstring pDstFileName = GetDstFileName();

    BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), 0, 0, 0, COPY_FILE_FAIL_IF_EXISTS);

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

void Test_CopyFileEx_SharingViolationSrcShareMode(DWORD dwShareMode)
{
    DEF_TESTLOG_T("Test_CopyFileEx_SharingViolationSrcShareMode");
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode);

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

        BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), 0, 0, 0, COPY_FILE_FAIL_IF_EXISTS);

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
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_CopyFileEx_SharingViolationSrc()
{
    Test_CopyFileEx_SharingViolationSrcShareMode(0);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_WRITE);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_DELETE);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE);
    Test_CopyFileEx_SharingViolationSrcShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
}

void CopyFileEx_ExistingDst(TestLog& log, BOOL bFailIfExists)
{
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

    BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), 0, 0, 0, bFailIfExists ? COPY_FILE_FAIL_IF_EXISTS : 0);

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

void Test_CopyFileEx_ExistingDstFail()
{
    DEF_TESTLOG_T("Test_CopyFile_ExistingDstFail");

    CopyFileEx_ExistingDst(log, TRUE);

    log.Ok();
}

void Test_CopyFileEx_ExistingDstNoFail()
{
    DEF_TESTLOG_T("Test_CopyFile_ExistingDstNoFail");

    CopyFileEx_ExistingDst(log, FALSE);

    log.Ok();
}

void Test_CopyFileEx_ExistingDstSharingViolationShareMode(DWORD dwShareMode)
{
    DEF_TESTLOG_T("Test_CopyFileEx_ExistingDstSharingViolationShareMode");
    log.GetStream(TestLog::MT_MESSAGE) << L"dwShareMode " << apiCreateFile.GetString_dwShareMode(dwShareMode);

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

    {
        File f(pDstFileName, GENERIC_READ, dwShareMode, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            return;
        }

        BOOL result = apiCopyFileEx(pSrcFileName.c_str(), pDstFileName.c_str(), 0, 0, 0, COPY_FILE_FAIL_IF_EXISTS);

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
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
    }
    if(!DeleteFileOrCheck(log, pDstFileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        return;
    }

    log.Ok();
}

void Test_CopyFileEx_ExistingDstSharingViolation()
{
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(0);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_DELETE);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_DELETE);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_WRITE | FILE_SHARE_DELETE);
    Test_CopyFileEx_ExistingDstSharingViolationShareMode(FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);
}