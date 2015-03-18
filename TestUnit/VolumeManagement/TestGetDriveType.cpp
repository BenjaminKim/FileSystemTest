#include "stdafx.h"
#include "TestGetDriveType.h"
#include "VolumeManagement/ApiGetDriveType.h"

using namespace std;

void Test_GetDriveTypeAll()
{
    //Test_GetDriveType(L"A:\\");
    Test_GetDriveType(L"B:\\");
    Test_GetDriveType(L"C:\\");
    Test_GetDriveType(L"D:\\");
    Test_GetDriveType(L"E:\\");
    Test_GetDriveType(L"F:\\");
    Test_GetDriveType(L"G:\\");
    Test_GetDriveType(L"H:\\");
    Test_GetDriveType(L"I:\\");
    Test_GetDriveType(L"J:\\");
    Test_GetDriveType(L"K:\\");
    Test_GetDriveType(L"L:\\");
    Test_GetDriveType(L"M:\\");
    Test_GetDriveType(L"N:\\");
    Test_GetDriveType(L"O:\\");
    Test_GetDriveType(L"P:\\");
    Test_GetDriveType(L"Q:\\");
    Test_GetDriveType(L"R:\\");
    Test_GetDriveType(L"S:\\");
    Test_GetDriveType(L"T:\\");
    Test_GetDriveType(L"U:\\");
    Test_GetDriveType(L"V:\\");
    Test_GetDriveType(L"W:\\");
    Test_GetDriveType(L"X:\\");
    Test_GetDriveType(L"Y:\\");
    Test_GetDriveType(L"Z:\\");
}

void Test_GetDriveType(const wstring& drive)
{
    DEF_TESTLOG_T("Test_GetDriveType");
    log.GetStream(TestLog::MT_MESSAGE) << L"drive " << drive << endl;

    apiGetDriveType(drive.c_str());

    log.Ok();
}