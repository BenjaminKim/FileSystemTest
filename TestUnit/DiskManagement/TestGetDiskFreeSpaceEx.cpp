#include "stdafx.h"
#include "TestGetDiskFreeSpaceEx.h"
#include "DiskManagement/ApiGetDiskFreeSpaceEx.h"

using namespace std;

void Test_GetDiskFreeSpaceEx(const std::wstring& rootPathName)
{
    DEF_TESTLOG_T("GetDiskFreeSpaceEx");

    ULARGE_INTEGER FreeBytesAvailable;
    ULARGE_INTEGER TotalNumberOfBytes;
    ULARGE_INTEGER TotalNumberOfFreeBytes;

    if(!apiGetDiskFreeSpaceEx(rootPathName.c_str(), &FreeBytesAvailable, &TotalNumberOfBytes, &TotalNumberOfFreeBytes))
    {
        return;
    }

    log.Ok();
}

void Test_GetDiskFreeSpaceEx_AllRootPath()
{
    //Test_GetDiskFreeSpaceEx(_T("A:\\"));
    Test_GetDiskFreeSpaceEx(_T("B:\\"));
    Test_GetDiskFreeSpaceEx(_T("C:\\"));
    Test_GetDiskFreeSpaceEx(_T("D:\\"));
    Test_GetDiskFreeSpaceEx(_T("E:\\"));
    Test_GetDiskFreeSpaceEx(_T("F:\\"));
    Test_GetDiskFreeSpaceEx(_T("G:\\"));
    Test_GetDiskFreeSpaceEx(_T("H:\\"));
    Test_GetDiskFreeSpaceEx(_T("I:\\"));
    Test_GetDiskFreeSpaceEx(_T("J:\\"));
    Test_GetDiskFreeSpaceEx(_T("K:\\"));
    Test_GetDiskFreeSpaceEx(_T("L:\\"));
    Test_GetDiskFreeSpaceEx(_T("M:\\"));
    Test_GetDiskFreeSpaceEx(_T("N:\\"));
    Test_GetDiskFreeSpaceEx(_T("O:\\"));
    Test_GetDiskFreeSpaceEx(_T("P:\\"));
    Test_GetDiskFreeSpaceEx(_T("Q:\\"));
    Test_GetDiskFreeSpaceEx(_T("R:\\"));
    Test_GetDiskFreeSpaceEx(_T("S:\\"));
    Test_GetDiskFreeSpaceEx(_T("T:\\"));
    Test_GetDiskFreeSpaceEx(_T("U:\\"));
    Test_GetDiskFreeSpaceEx(_T("V:\\"));
    Test_GetDiskFreeSpaceEx(_T("W:\\"));
    Test_GetDiskFreeSpaceEx(_T("X:\\"));
    Test_GetDiskFreeSpaceEx(_T("Y:\\"));
    Test_GetDiskFreeSpaceEx(_T("Z:\\"));
}