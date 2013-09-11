#include "stdafx.h"
#include "TestGetLogicalDrives.h"
#include "VolumeManagement/ApiGetLogicalDrives.h"

using namespace std;

void Test_GetLogicalDrives()
{
    DEF_TESTLOG_T("Test_GetLogicalDrives");

    apiGetLogicalDrives();

    log.Ok();
}