#pragma once

void Test_CopyFileEx_Normal();
void Test_CopyFileEx_NoExistingSrc();
void Test_CopyFileEx_SharingViolationSrcShareMode(DWORD dwShareMode);
void Test_CopyFileEx_SharingViolationSrc();
void Test_CopyFileEx_ExistingDstFail();
void Test_CopyFileEx_ExistingDstNoFail();
void Test_CopyFileEx_ExistingDstSharingViolationShareMode(DWORD dwShareMode);
void Test_CopyFileEx_ExistingDstSharingViolation();
void Test_CopyFileEx_Cancle();

inline void Test_CopyFileEx_All()
{
    Test_CopyFileEx_Normal();
    Test_CopyFileEx_Cancle();
    Test_CopyFileEx_NoExistingSrc();
    Test_CopyFileEx_SharingViolationSrc();
    Test_CopyFileEx_ExistingDstFail();
    Test_CopyFileEx_ExistingDstNoFail();
    Test_CopyFileEx_ExistingDstSharingViolation();
}
