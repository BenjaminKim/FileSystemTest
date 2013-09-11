#include "stdafx.h"
#include "TestFindFirstVolume.h"
#include "VolumeManagement/ApiFindFirstVolume.h"
#include "VolumeManagement/ApiFindNextVolume.h"
#include "VolumeManagement/ApiFindVolumeClose.h"
#include "VolumeManagement/ApiQueryDosDevice.h"
#include "VolumeManagement/ApiGetVolumePathNamesForVolumeName.h"
#include "VolumeManagement/ApiGetVolumeNameForVolumeMountPoint.h"
#include "VolumeManagement/ApiFindFirstVolumeMountPoint.h"
#include "VolumeManagement/ApiFindNextVolumeMountPoint.h"
#include "VolumeManagement/ApiFindVolumeMountPointClose.h"

using namespace std;

void FindVolumeMountPoint(TestLog& log, PWCHAR volumeName)
{
    WCHAR volumeMountPoint[MAX_PATH] = { 0 };
    WCHAR volumeName2[MAX_PATH] = { 0 };
    HANDLE hFind;
    BOOL findNext;

    hFind = apiFindFirstVolumeMountPoint(volumeName, volumeMountPoint, _countof(volumeMountPoint));

    if(hFind == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"FindFirstVolumeMountPoint" << endl;
        return;
    }

    for(;;)
    {
        apiGetVolumeNameForVolumeMountPoint(volumeMountPoint, volumeName2, _countof(volumeName2));
        findNext = apiFindNextVolumeMountPoint(hFind, volumeMountPoint, _countof(volumeMountPoint));
        if(!findNext)
        {
            if(GetLastError() != ERROR_NO_MORE_FILES)
            {
                log.GetStream(TestLog::MT_ERROR) << L"FindNextVolumeMountPoint" << endl;
            }

            break;
        }
    }

    apiFindVolumeMountPointClose(hFind);
}

void GetVolumePaths(TestLog& log,PWCHAR volumeName)
{
    ApiGetVolumePathNamesForVolumeName apiGetVolumePathNamesForVolumeName;
    ApiGetVolumeNameForVolumeMountPoint apiGetVolumeNameForVolumeMountPoint; // verify

    WCHAR  names[MAX_PATH + 1] = {0, };
    BOOL   success = FALSE;
    DWORD  charCount;

    for(;;)
    {
        charCount = 0;
        success = apiGetVolumePathNamesForVolumeName(
            volumeName, names, _countof(names), &charCount);

        if(success)
        {
            WCHAR volumeName2[MAX_PATH];
            for(PWCHAR nameIdx = names;
                nameIdx[0] != L'\0';
                nameIdx += wcslen(nameIdx) + 1) 
            {
                apiGetVolumeNameForVolumeMountPoint(nameIdx, volumeName2, _countof(volumeName2)); 
            }
            
            break;
        }

        if(GetLastError() != ERROR_MORE_DATA)
        {
            log.GetStream(TestLog::MT_ERROR) << L"GetVolumePathNamesForVolumeName" << endl;
            break;
        }

        // more data
    }
}

void Test_FindFirstVolume()
{
    DEF_TESTLOG_T("Test_FindFirstVolume");
    ApiFindFirstVolume apiFindFirstVolume;
    ApiFindNextVolume apiFindNextVolume;
    ApiFindVolumeClose apiFindVolumeClose;
    ApiQueryDosDevice apiQueryDosDevice;

    DWORD  charCount            = 0;
    WCHAR  volumeName[MAX_PATH] = {0, };
    WCHAR  deviceName[MAX_PATH] = {0, };
    HANDLE findHandle           = INVALID_HANDLE_VALUE;
    size_t index                = 0;
    BOOL   success              = FALSE;

    
    findHandle = apiFindFirstVolume(volumeName, _countof(volumeName));

    if(findHandle == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"FindFirstVolume" << endl;
        return;
    }

    for(;;)
    {
        //
        //  Skip the \\?\ prefix and remove the trailing backslash.
        index = wcslen(volumeName) - 1;

        if (volumeName[0]     != L'\\' ||
            volumeName[1]     != L'\\' ||
            volumeName[2]     != L'?'  ||
            volumeName[3]     != L'\\' ||
            volumeName[index] != L'\\')
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindFirstVolume, bad path" << endl;
            break;
        }

        //
        //  QueryDosDeviceW doesn't allow a trailing backslash,
        //  so temporarily remove it.
        volumeName[index] = L'\0';

        charCount = apiQueryDosDevice(&volumeName[4], deviceName, _countof(deviceName)); 

        volumeName[index] = L'\\';

        if(charCount == 0)
        {
            log.GetStream(TestLog::MT_ERROR) << L"QueryDosDevice" << endl;
            break;
        }

        GetVolumePaths(log, volumeName);
        FindVolumeMountPoint(log, volumeName);

        success = apiFindNextVolume(findHandle, volumeName, _countof(volumeName));

        if(!success)
        {
            if(GetLastError() != ERROR_NO_MORE_FILES)
            {
                log.GetStream(TestLog::MT_ERROR) << L"FindNextVolume" << endl;
            }

            break;
        }
    }

    apiFindVolumeClose(findHandle);

    FindVolumeMountPoint(log, L"C:\\");

    log.Ok();
}
