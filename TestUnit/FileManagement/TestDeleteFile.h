#pragma once


void Test_DeleteFile_Normal();
void Test_DeleteFile_ReadOnly();
void Test_DeleteFile_OpenFile();
void Test_DeleteFile_SharingViolation();
void Test_DeleteFile_NoExist();
void Test_DeleteFile_DeletedFile();
void Test_DeleteFile_DeletedFileSharingViolation();

inline void Test_DeleteFile_All()
{
    Test_DeleteFile_Normal();
    Test_DeleteFile_ReadOnly();
    Test_DeleteFile_OpenFile();
    Test_DeleteFile_SharingViolation();
    Test_DeleteFile_NoExist();
    Test_DeleteFile_DeletedFile();
    Test_DeleteFile_DeletedFileSharingViolation();
}
