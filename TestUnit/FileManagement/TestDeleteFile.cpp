#include "stdafx.h"
#include "TestDeleteFile.h"
#include "FileManagement/ApiDeleteFile.h"
#include "../File.h"
#include "FileManagement/ApiSetFileAttributes.h"

using namespace std;

/**
- �׳� ����� ���
- �ٸ� ������ DELETE ���� ��������� ������ ���� ���� �� ���� �õ�
*/
void Test_DeleteFile_Normal()
{
    DEF_TESTLOG_T("Test_DeleteFile_Normal");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL iOk = apiDeleteFile(fileName.c_str());

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}

// �б� ���� ������ ����
void Test_DeleteFile_ReadOnly()
{
    DEF_TESTLOG_T("Test_DeleteFile_ReadOnly");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    apiSetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_READONLY);
    BOOL iOk = apiDeleteFile(fileName.c_str());

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"�б� ���� Cannot delete the file. -������ �� �־�� �Ѵ�." << endl;
            return;
        }
    }

    log.Ok();
}

void Test_DeleteFile_OpenFile()
{
    DEF_TESTLOG_T("Test_DeleteFile_OpenFile");
    wstring fileName = GetTestFileName(L"Test_DeleteFile_OpenFile");

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL iOk = FALSE;
    {
        File f(fileName, GENERIC_READ, FILE_SHARE_DELETE, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            if(!DeleteFileOrCheck(log, fileName.c_str()))
            {
                log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            }
            return;
        }

        iOk = apiDeleteFile(fileName.c_str());

        BOOL result = f.CloseHandle();
        if(!result)
        {
            // ���� �߻����� �ʴ´�.
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
        }
    }

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}

void Test_DeleteFile_SharingViolation()
{
    DEF_TESTLOG_T("Test_DeleteFile_SharingViolation");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL iOk = FALSE;
    {
        File f(fileName, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            if(!DeleteFileOrCheck(log, fileName.c_str()))
            {
                log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            }
            return;
        }

        iOk = apiDeleteFile(fileName.c_str());

        BOOL result = f.CloseHandle();
        if(!result)
        {
            // ���� �߻����� �ʴ´�.
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
        }
    }

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}

void Test_DeleteFile_NoExist()
{
    DEF_TESTLOG_T("Test_DeleteFile_NoExist");
    wstring fileName = GetTestFileName();

    BOOL iOk = apiDeleteFile(fileName.c_str());

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}

void Test_DeleteFile_DeletedFile()
{
    DEF_TESTLOG_T("Test_DeleteFile_DeletedFile");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL iOk = FALSE;
    {
        File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
                GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L")" << endl;
            if(!DeleteFileOrCheck(log, fileName.c_str()))
            {
                log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            }
            return;
        }

        DeleteFileW(fileName.c_str());
        //// delete pending

        iOk = apiDeleteFile(fileName.c_str());

        // ���������� DELETE_PENDING ��������� ERROR_ACCESS_DENIED �߻�
        BOOL result = f.CloseHandle();
        if(!result)
        {
            // ���� �߻����� �ʴ´�.
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
        }
    }

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}

void Test_DeleteFile_DeletedFileSharingViolation()
{
    DEF_TESTLOG_T("Test_DeleteFile_DeletedFileSharingViolation");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    BOOL iOk = FALSE;
    {
        File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
                GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L")" << endl;
            if(!DeleteFileOrCheck(log, fileName.c_str()))
            {
                log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            }
            return;
        }

        DeleteFileW(fileName.c_str());
        //// delete pending

        iOk = apiDeleteFile(fileName.c_str());

        // ���������� DELETE_PENDING ��������� ERROR_ACCESS_DENIED �߻�
        // ERROR_SHARING_VIOLATION ������ �߻����� �ʴ´�.
        // ��, ������ �������ٴ� ���� ���� ó���ȴ�.
        BOOL result = f.CloseHandle();
        if(!result)
        {
            // ���� �߻����� �ʴ´�.
            log.GetStream(TestLog::MT_ERROR) << L"CloseHandle" << endl;
        }
    }

    if(!iOk)
    {
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            return;
        }
    }

    log.Ok();
}