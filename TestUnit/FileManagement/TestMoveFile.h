#pragma once


void Test_MoveFile_Normal();
void Test_MoveFile_NoExistingSrc();
void Test_MoveFile_SharingViolationSrcShareMode(DWORD dwShareMode);
void Test_MoveFile_SharingViolationSrc();
void Test_MoveFile_ExistingDst();
void Test_MoveFile_ExistingDstSharingViolationShareMode(DWORD dwShareMode);
void Test_MoveFile_ExistingDstSharingViolation();
void Test_RenameFile_ShareAll();
void Test_RenameFile_Share(DWORD dwShareMode);

inline void Test_MoveFile_All()
{
    Test_MoveFile_Normal();
    Test_MoveFile_NoExistingSrc();
    Test_MoveFile_SharingViolationSrc();
    Test_MoveFile_ExistingDst();
    Test_MoveFile_ExistingDstSharingViolation();
    Test_RenameFile_ShareAll();
}