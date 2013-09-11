#include "stdafx.h"
#include "TestGetVolumePathName.h"
#include "VolumeManagement/ApiGetVolumePathName.h"

using namespace std;

void Test_GetVolumePathName()
{
    DEF_TESTLOG_T("Test_GetVolumePathName, 현재 기본 디렉토리와 C,D,E,F,X,Y,Z 드라이브 대해 볼륨 패스를 얻어본다.");

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
