#include "stdafx.h"
#include "TestGetFileSize.h"
#include "FileManagement/ApiGetFileSize.h"
#include "../File.h"
#include "FileManagement/ApiDeleteFile.h"

using namespace std;

void Test_GetFileSize()
{
    DEF_TESTLOG_T("GetFileSize, Get file size a specific file");

    wstring fileName = GetTestFileName(L"Test_GetFileSize");
    if(!MakeFile(log, fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    DWORD dwSizeHigh;

    File f(fileName);
    DWORD dwSizeLow = apiGetFileSize(f, &dwSizeHigh);

    if(f.IsValidHandle())
    {
        f.CloseHandle();
    }

    if(dwSizeLow == INVALID_FILE_SIZE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFileSize failed." << endl;

        BOOL fOk = uDeleteFile(fileName.c_str());

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
            return;
        }

        return;
    }

    BOOL fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }   

    log.Ok();
}