#include "stdafx.h"
#include "TestGetTempPath.h"
#include "FileManagement/ApiGetTempPath.h"

using namespace std;

void Test_GetTempPath()
{
    DEF_TESTLOG_T("GetTempPath, 임시 경로를 얻어본다.");

    TCHAR buf[MAX_PATH];
    apiGetTempPath(_countof(buf), buf);

    log.Ok();
}