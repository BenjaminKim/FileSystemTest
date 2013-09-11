#pragma once

void Test_SetFileInformationByHandleAll();
static void Test_SetFileInformationByHandle_Disposition_NormalFile();
static void Test_SetFileInformationByHandle_Disposition_ReadOnlyFile1();
static void Test_SetFileInformationByHandle_Disposition_ReadOnlyFile2();
static void Test_SetFileInformationByHandle_Delete_Twice();
static void Test_SetFileInformationByHandle_Delete_No_Have_Delete_DesireAccess();
void Test_SetFileInformationByHandle_FileTime(LARGE_INTEGER CreationTime,
                                                     LARGE_INTEGER LastAccessTime,
                                                     LARGE_INTEGER LastWriteTime,
                                                     LARGE_INTEGER ChangeTime);
void Test_Writefile_FileTime();
void Test_DeleteFile_RenamedFile();

inline void Test_SetFileInformationByHandle_FileTimeAll()
{
    LARGE_INTEGER Time1;
    Time1.QuadPart = 500000000;

    LARGE_INTEGER LNULL = { 0 };

    LARGE_INTEGER Minus;
    Minus.QuadPart = -1;

    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, LNULL, LNULL);
    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, LNULL, Time1);
    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, Time1, LNULL);
    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, Time1, Time1);
    Test_SetFileInformationByHandle_FileTime(LNULL, Time1, LNULL, LNULL);
    Test_SetFileInformationByHandle_FileTime(LNULL, Time1, LNULL, Time1);
    Test_SetFileInformationByHandle_FileTime(LNULL, Time1, Time1, LNULL);
    Test_SetFileInformationByHandle_FileTime(LNULL, Time1, Time1, Time1);
    Test_SetFileInformationByHandle_FileTime(Time1, LNULL, LNULL, LNULL);
    Test_SetFileInformationByHandle_FileTime(Time1, LNULL, LNULL, Time1);
    Test_SetFileInformationByHandle_FileTime(Time1, LNULL, Time1, LNULL);
    Test_SetFileInformationByHandle_FileTime(Time1, LNULL, Time1, Time1);
    Test_SetFileInformationByHandle_FileTime(Time1, Time1, LNULL, LNULL);
    Test_SetFileInformationByHandle_FileTime(Time1, Time1, LNULL, Time1);
    Test_SetFileInformationByHandle_FileTime(Time1, Time1, Time1, LNULL);
    Test_SetFileInformationByHandle_FileTime(Time1, Time1, Time1, Time1);

    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, LNULL, Minus);
    Test_SetFileInformationByHandle_FileTime(LNULL, LNULL, Time1, Minus);
    Test_SetFileInformationByHandle_FileTime(LNULL, Time1, Minus, Minus);
    Test_SetFileInformationByHandle_FileTime(Time1, Minus, Minus, Minus);
    Test_SetFileInformationByHandle_FileTime(Minus, Minus, Minus, Minus);

    Test_Writefile_FileTime();
    Test_DeleteFile_RenamedFile();
}