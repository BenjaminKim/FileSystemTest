#pragma once

void Test_CopyFile_Normal();
void Test_CopyFile_NoExistingSrc();
void Test_CopyFile_SharingViolationSrcShareMode(DWORD dwShareMode);
void Test_CopyFile_SharingViolationSrc();
void Test_CopyFile_ExistingDstFail();
void Test_CopyFile_ExistingDstNoFail();
void Test_CopyFile_ExistingDstSharingViolationShareMode(DWORD dwShareMode);
void Test_CopyFile_ExistingDstSharingViolation();

inline void Test_CopyFile_All()
{
    Test_CopyFile_Normal();
    Test_CopyFile_NoExistingSrc();
    Test_CopyFile_SharingViolationSrc();
    Test_CopyFile_ExistingDstFail();
    Test_CopyFile_ExistingDstNoFail();
    Test_CopyFile_ExistingDstSharingViolation();
}
