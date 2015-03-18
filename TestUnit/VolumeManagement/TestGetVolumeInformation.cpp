#include "stdafx.h"
#include "TestGetVolumeInformation.h"
#include "VolumeManagement/ApiGetVolumeInformation.h"

using namespace std;

void Test_GetVolumeInformationAll()
{
    //Test_GetVolumeInformation(L"A:\\");
    Test_GetVolumeInformation(L"B:\\");
    Test_GetVolumeInformation(L"C:\\");
    Test_GetVolumeInformation(L"D:\\");
    Test_GetVolumeInformation(L"E:\\");
    Test_GetVolumeInformation(L"F:\\");
    Test_GetVolumeInformation(L"G:\\");
    Test_GetVolumeInformation(L"H:\\");
    Test_GetVolumeInformation(L"I:\\");
    Test_GetVolumeInformation(L"J:\\");
    Test_GetVolumeInformation(L"K:\\");
    Test_GetVolumeInformation(L"L:\\");
    Test_GetVolumeInformation(L"M:\\");
    Test_GetVolumeInformation(L"N:\\");
    Test_GetVolumeInformation(L"O:\\");
    Test_GetVolumeInformation(L"P:\\");
    Test_GetVolumeInformation(L"Q:\\");
    Test_GetVolumeInformation(L"R:\\");
    Test_GetVolumeInformation(L"S:\\");
    Test_GetVolumeInformation(L"T:\\");
    Test_GetVolumeInformation(L"U:\\");
    Test_GetVolumeInformation(L"V:\\");
    Test_GetVolumeInformation(L"W:\\");
    Test_GetVolumeInformation(L"X:\\");
    Test_GetVolumeInformation(L"Y:\\");
    Test_GetVolumeInformation(L"Z:\\");
}

void Test_GetVolumeInformation(const wstring& rootPathName)
{
    DEF_TESTLOG_T("Test_GetVolumeInformation");

    TCHAR pszVolumeNameBuffer[MAX_PATH] = { 0 };
    DWORD nVolumeNameSize = MAX_PATH;
    DWORD dwVolumeSerialNumber;
    DWORD dwMaximumComponentLength;
    DWORD dwFileSystemFlags;
    TCHAR pszFileSystemNameBuffer[MAX_PATH] = { 0 };
    DWORD nFileSystemNameSize = MAX_PATH;

    BOOL fOk = apiGetVolumeInformation(rootPathName.c_str(), pszVolumeNameBuffer, nVolumeNameSize,
        &dwVolumeSerialNumber, &dwMaximumComponentLength, &dwFileSystemFlags, pszFileSystemNameBuffer, nFileSystemNameSize);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"RemoveDirectory Function was failed." << endl;
        return;
    }

    log.Ok();
}