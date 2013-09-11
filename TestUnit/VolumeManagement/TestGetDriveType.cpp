#include "stdafx.h"
#include "TestGetDriveType.h"
#include "VolumeManagement/ApiGetDriveType.h"

using namespace std;

void Test_GetDriveTypeAll()
{
    //Test_GetDriveType(_T("A:\\"));
    Test_GetDriveType(_T("B:\\"));
    Test_GetDriveType(_T("C:\\"));
    Test_GetDriveType(_T("D:\\"));
    Test_GetDriveType(_T("E:\\"));
    Test_GetDriveType(_T("F:\\"));
    Test_GetDriveType(_T("G:\\"));
    Test_GetDriveType(_T("H:\\"));
    Test_GetDriveType(_T("I:\\"));
    Test_GetDriveType(_T("J:\\"));
    Test_GetDriveType(_T("K:\\"));
    Test_GetDriveType(_T("L:\\"));
    Test_GetDriveType(_T("M:\\"));
    Test_GetDriveType(_T("N:\\"));
    Test_GetDriveType(_T("O:\\"));
    Test_GetDriveType(_T("P:\\"));
    Test_GetDriveType(_T("Q:\\"));
    Test_GetDriveType(_T("R:\\"));
    Test_GetDriveType(_T("S:\\"));
    Test_GetDriveType(_T("T:\\"));
    Test_GetDriveType(_T("U:\\"));
    Test_GetDriveType(_T("V:\\"));
    Test_GetDriveType(_T("W:\\"));
    Test_GetDriveType(_T("X:\\"));
    Test_GetDriveType(_T("Y:\\"));
    Test_GetDriveType(_T("Z:\\"));
}

void Test_GetDriveType(const wstring& drive)
{
    DEF_TESTLOG_T("Test_GetDriveType");
    log.GetStream(TestLog::MT_MESSAGE) << L"drive " << drive << endl;

    apiGetDriveType(drive.c_str());

    log.Ok();
}