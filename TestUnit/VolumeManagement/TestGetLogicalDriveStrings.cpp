#include "stdafx.h"
#include "TestGetLogicalDriveStrings.h"
#include "VolumeManagement/ApiGetLogicalDriveStrings.h"

using namespace std;

void Test_GetLogicalDriveStrings()
{
    DEF_TESTLOG_T("Test_GetLogicalDriveStrings");

    TCHAR psz[MAX_PATH];

    apiGetLogicalDriveStrings(_countof(psz), psz);

    log.Ok();
}