#include "stdafx.h"
#include "TestSetFileAttributes.h"
#include "FileManagement/ApiSetFileAttributes.h"
#include "FileManagement/ApiGetFileAttributes.h"
#include "../Combinator.h"
#include "FileManagement/ApiDeleteFile.h"
#include "DirectoryManagement/ApiCreateDirectory.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"

using namespace std;

void Test_SetFileAttributesAll()
{
    BitCombinator<DWORD> c;
    c.AddAllSingleBit(
        FILE_ATTRIBUTE_READONLY |
        FILE_ATTRIBUTE_HIDDEN |
        FILE_ATTRIBUTE_SYSTEM |
        // FILE_ATTRIBUTE_DIRECTORY |
        FILE_ATTRIBUTE_ARCHIVE |
        //FILE_ATTRIBUTE_DEVICE |
        FILE_ATTRIBUTE_NORMAL |
        //FILE_ATTRIBUTE_TEMPORARY |
        // FILE_ATTRIBUTE_SPARSE_FILE |
        //FILE_ATTRIBUTE_REPARSE_POINT |
        //FILE_ATTRIBUTE_COMPRESSED |
        // FILE_ATTRIBUTE_OFFLINE |
        // FILE_ATTRIBUTE_NOT_CONTENT_INDEXED |
        // FILE_ATTRIBUTE_ENCRYPTED |
        // FILE_ATTRIBUTE_VIRTUAL |
        0);

    DWORD uBit = 0;
    while((uBit = c.Next(uBit)) != 0)
    {
        Test_SetFileAttributes(uBit);
    }

    Test_SetFileAttributes(0);
 

    uBit = 0;
    while((uBit = c.Next(uBit)) != 0)
    {
        Test_SetDirAttributes(uBit);
    }

    Test_SetDirAttributes(0);
    Test_SetDirAttributes(FILE_ATTRIBUTE_DIRECTORY);
    Test_SetDirAttributes(FILE_ATTRIBUTE_DEVICE);
    Test_SetDirAttributes(FILE_ATTRIBUTE_TEMPORARY);
    Test_SetDirAttributes(FILE_ATTRIBUTE_SPARSE_FILE);
    Test_SetDirAttributes(FILE_ATTRIBUTE_REPARSE_POINT);
    Test_SetDirAttributes(FILE_ATTRIBUTE_COMPRESSED);
    Test_SetDirAttributes(FILE_ATTRIBUTE_OFFLINE);
    Test_SetDirAttributes(FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
    Test_SetDirAttributes(FILE_ATTRIBUTE_ENCRYPTED);
    Test_SetDirAttributes(FILE_ATTRIBUTE_VIRTUAL);
}

void Test_SetFileAttributes(DWORD dwFileAttributes)
{
    DEF_TESTLOG_T("SetFileAttributes, 파일에 대해 모든 플래그의 조합을 입력해봅니다.");
    std::wstring fileName = GetTestFileName();

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 생성할 수 없습니다." << GetLastErrorStr() << endl;
        return;
    }
   
    BOOL fOk = apiSetFileAttributes(fileName.c_str(), dwFileAttributes);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileAttributeApi가 실패했습니다." << endl;

        uSetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_NORMAL);

        fOk = uDeleteFile(fileName.c_str());

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제할 수 없습니다." << GetLastErrorStr() << endl;
            return;
        }
    }

    apiGetFileAttributes(fileName.c_str());
    uSetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_NORMAL);
    fOk = uDeleteFile(fileName.c_str());
    
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제할 수 없습니다." << GetLastErrorStr() << endl;
        return;
    }

    log.Ok();
}

void Test_SetDirAttributes(DWORD dwFileAttributes)
{
    DEF_TESTLOG_T("SetFileAttributes, 디렉토리에 대해 모든 플래그의 조합을 입력해봅니다.");
    std::wstring fileName = GetTestFileName();

    BOOL fOk = uCreateDirectory(fileName.c_str(), 0);

    apiGetFileAttributes(fileName.c_str());

    fOk = apiSetFileAttributes(fileName.c_str(), dwFileAttributes);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"SetFileAttributeApi가 실패했습니다." << endl;

        uSetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_DIRECTORY);

        fOk = uRemoveDirectory(fileName.c_str());

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 삭제할 수 없습니다." << GetLastErrorStr() << endl;
            return;
        }
    }

    apiGetFileAttributes(fileName.c_str());

    // 읽기 전용 플래그가 있으면 삭제가 안되므로 다시 기본 속성으로 되돌린다.
    uSetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_DIRECTORY);
    fOk = uRemoveDirectory(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리를 삭제할 수 없습니다." << GetLastErrorStr() << endl;
        return;
    }

    log.Ok();
}