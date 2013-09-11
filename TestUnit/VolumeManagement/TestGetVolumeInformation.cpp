#include "stdafx.h"
#include "TestGetVolumeInformation.h"
#include "VolumeManagement/ApiGetVolumeInformation.h"

using namespace std;

void Test_GetVolumeInformationAll()
{
    //Test_GetVolumeInformation(_T("A:\\"));
    Test_GetVolumeInformation(_T("B:\\"));
    Test_GetVolumeInformation(_T("C:\\"));
    Test_GetVolumeInformation(_T("D:\\"));
    Test_GetVolumeInformation(_T("E:\\"));
    Test_GetVolumeInformation(_T("F:\\"));
    Test_GetVolumeInformation(_T("G:\\"));
    Test_GetVolumeInformation(_T("H:\\"));
    Test_GetVolumeInformation(_T("I:\\"));
    Test_GetVolumeInformation(_T("J:\\"));
    Test_GetVolumeInformation(_T("K:\\"));
    Test_GetVolumeInformation(_T("L:\\"));
    Test_GetVolumeInformation(_T("M:\\"));
    Test_GetVolumeInformation(_T("N:\\"));
    Test_GetVolumeInformation(_T("O:\\"));
    Test_GetVolumeInformation(_T("P:\\"));
    Test_GetVolumeInformation(_T("Q:\\"));
    Test_GetVolumeInformation(_T("R:\\"));
    Test_GetVolumeInformation(_T("S:\\"));
    Test_GetVolumeInformation(_T("T:\\"));
    Test_GetVolumeInformation(_T("U:\\"));
    Test_GetVolumeInformation(_T("V:\\"));
    Test_GetVolumeInformation(_T("W:\\"));
    Test_GetVolumeInformation(_T("X:\\"));
    Test_GetVolumeInformation(_T("Y:\\"));
    Test_GetVolumeInformation(_T("Z:\\"));
}

void Test_GetVolumeInformation(const wstring& rootPathName)
{
    DEF_TESTLOG_T("Test_GetVolumeInformation, 볼륨 루트들에 대한 케이스를 확인한다.");

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