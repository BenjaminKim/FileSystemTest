#include "stdafx.h"
#include "TestGetShortPathName.h"
#include "FileManagement/ApiGetShortPathName.h"

using namespace std;

void Test_GetShortPathName()
{
    DEF_TESTLOG_T("GetShortPathName");
    
    wstring fileName = GetTestFileName(L"GetShortPathName");

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file." << endl;
        return;
    }

    TCHAR szShortPath[MAX_PATH] = { 0 };
    apiGetShortPathName(fileName.c_str(), szShortPath, _countof(szShortPath));

    if(!uDeleteFile(fileName.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to delete the file." << endl;
        return;
    }

    log.Ok();
}