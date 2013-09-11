#include "stdafx.h"
#include "TestCreateDirectoryEx.h"
#include "DirectoryManagement/ApiCreateDirectoryEx.h"
#include "../Combinator.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"
#include "FileManagement/ApiSetFileAttributes.h"

using namespace std;

void Test_CreateDirectoryExAll()
{
    BitCombinator<DWORD> c;

    c.AddAllSingleBit(
        FILE_ATTRIBUTE_READONLY |
        FILE_ATTRIBUTE_HIDDEN |
        FILE_ATTRIBUTE_SYSTEM |
        // FILE_ATTRIBUTE_DIRECTORY |
        FILE_ATTRIBUTE_ARCHIVE |
        FILE_ATTRIBUTE_DEVICE |
        FILE_ATTRIBUTE_NORMAL |
        //FILE_ATTRIBUTE_TEMPORARY |
        // FILE_ATTRIBUTE_SPARSE_FILE |
        FILE_ATTRIBUTE_REPARSE_POINT |
        FILE_ATTRIBUTE_COMPRESSED |
        // FILE_ATTRIBUTE_OFFLINE |
        // FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
        // FILE_ATTRIBUTE_ENCRYPTED |
        // FILE_ATTRIBUTE_VIRTUAL |
        0);

    DWORD uBit = 0;
    while((uBit = c.Next(uBit)) != 0)
    {
        Test_CreateDirectoryEx(uBit);
    }

    Test_CreateDirectoryEx(FILE_ATTRIBUTE_TEMPORARY);
}

void Test_CreateDirectoryEx(DWORD dwAttribute)
{
    DEF_TESTLOG_T("CreateDirectoryEx, 템플릿 디렉토리의 속성조합을 다르게 해서 테스트");
    log.GetStream(TestLog::MT_MESSAGE) << L"Template dir attributes is " << GetString_dwFileAttributes(dwAttribute) << endl;;

    wstring templateDirName = GetTestFileName(_T("TestTemplateDirName"));
    wstring dirname = GetTestFileName(_T("CreateDirectoryEx"));

    BOOL fOk = CreateDirectoryWithAttributes(log, templateDirName, dwAttribute);

    if(!fOk)
    {
        uRemoveDirectory(templateDirName.c_str());
        uRemoveDirectory(dirname.c_str());
        return;
    }

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof sa;
    sa.lpSecurityDescriptor = 0;
    sa.bInheritHandle = TRUE;

    fOk = apiCreateDirectoryEx(templateDirName.c_str(), dirname.c_str(), &sa);
    DWORD dwLastError = GetLastError();
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateDirectoryExTest Api가 실패했습니다. " << GetErrorDefineString(dwLastError) << endl;
        uRemoveDirectory(templateDirName.c_str());
        uRemoveDirectory(dirname.c_str());
        return;
    }

    fOk = uSetFileAttributes(dirname.c_str(), FILE_ATTRIBUTE_NORMAL);
    fOk &= uSetFileAttributes(templateDirName.c_str(), FILE_ATTRIBUTE_NORMAL);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileAttributes Function was failed." << endl;
        uRemoveDirectory(templateDirName.c_str());
        uRemoveDirectory(dirname.c_str());
        return;
    }

    fOk = uRemoveDirectory(templateDirName.c_str());
    fOk &= uRemoveDirectory(dirname.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"RemoveDirectory Function was failed." << endl;
        return;
    }

    log.Ok();
}