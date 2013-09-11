#include "stdafx.h"
#include "TestGetCompressedFileSize.h"
#include "FileManagement/ApiGetCompressedFileSize.h"

using namespace std;

void Test_GetCompressedFileSize()
{
    DEF_TESTLOG_T("GetCompressedFileSize");

    wstring fileName = GetTestFileName(L"GetCompressedFileSize");

    if(!MakeFile(log, fileName, 100))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    DWORD dwFileHighSize;
    DWORD dwFileLowSize = apiGetCompressedFileSize(fileName.c_str(), &dwFileHighSize);

    log.GetStream(TestLog::MT_MESSAGE) << L"FileSize is " << FileSizeToString(dwFileHighSize, dwFileLowSize) << endl;

    uDeleteFile(fileName.c_str());

    log.Ok();
}