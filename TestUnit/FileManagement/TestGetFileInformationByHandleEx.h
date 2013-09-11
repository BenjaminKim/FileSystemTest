#pragma once


void Test_CopyFile_Normal();
void Test_CopyFile_NoExistingSrc();
void Test_CopyFile_SharingViolationSrcShareMode(DWORD dwShareMode);
void Test_CopyFile_SharingViolationSrc();
void Test_CopyFile_ExistingDstFail();
void Test_CopyFile_ExistingDstNoFail();
void Test_CopyFile_ExistingDstSharingViolationShareMode(DWORD dwShareMode);
void Test_CopyFile_ExistingDstSharingViolation();