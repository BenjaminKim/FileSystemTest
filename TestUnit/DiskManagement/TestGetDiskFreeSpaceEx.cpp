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
    //Test_GetDiskFreeSpaceEx(L"A:\\");
    Test_GetDiskFreeSpaceEx(L"B:\\");
    Test_GetDiskFreeSpaceEx(L"C:\\");
    Test_GetDiskFreeSpaceEx(L"D:\\");
    Test_GetDiskFreeSpaceEx(L"E:\\");
    Test_GetDiskFreeSpaceEx(L"F:\\");
    Test_GetDiskFreeSpaceEx(L"G:\\");
    Test_GetDiskFreeSpaceEx(L"H:\\");
    Test_GetDiskFreeSpaceEx(L"I:\\");
    Test_GetDiskFreeSpaceEx(L"J:\\");
    Test_GetDiskFreeSpaceEx(L"K:\\");
    Test_GetDiskFreeSpaceEx(L"L:\\");
    Test_GetDiskFreeSpaceEx(L"M:\\");
    Test_GetDiskFreeSpaceEx(L"N:\\");
    Test_GetDiskFreeSpaceEx(L"O:\\");
    Test_GetDiskFreeSpaceEx(L"P:\\");
    Test_GetDiskFreeSpaceEx(L"Q:\\");
    Test_GetDiskFreeSpaceEx(L"R:\\");
    Test_GetDiskFreeSpaceEx(L"S:\\");
    Test_GetDiskFreeSpaceEx(L"T:\\");
    Test_GetDiskFreeSpaceEx(L"U:\\");
    Test_GetDiskFreeSpaceEx(L"V:\\");
    Test_GetDiskFreeSpaceEx(L"W:\\");
    Test_GetDiskFreeSpaceEx(L"X:\\");
    Test_GetDiskFreeSpaceEx(L"Y:\\");
    Test_GetDiskFreeSpaceEx(L"Z:\\");
}