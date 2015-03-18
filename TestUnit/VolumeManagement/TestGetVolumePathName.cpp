#include "stdafx.h"
#include "TestGetVolumePathName.h"
#include "VolumeManagement/ApiGetVolumePathName.h"

using namespace std;

void Test_GetVolumePathName()
{
    DEF_TESTLOG_T("Test_GetVolumePathName");

    WCHAR volumeName[MAX_PATH];
    apiGetVolumePathName(GetWidTestBasePath().c_str(), volumeName, _countof(volumeName));
    apiGetVolumePathName(L"C:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"D:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"E:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"F:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"X:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"Y:\\", volumeName, _countof(volumeName));
    apiGetVolumePathName(L"Z:\\", volumeName, _countof(volumeName));

    log.Ok();
}
