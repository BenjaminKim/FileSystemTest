#include "stdafx.h"
#include "TestGetCurrentDirectory.h"
#include "DirectoryManagement/ApiGetCurrentDirectory.h"

using namespace std;

void Test_GetCurrentDirectory()
{
    DEF_TESTLOG_T("GetCurrentDirectory, ");
    
    TCHAR buf[MAX_PATH];
    if(!apiGetCurrentDirectory(_countof(buf), buf))
    {
        return;
    }

    log.Ok();
}