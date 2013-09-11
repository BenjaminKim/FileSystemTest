#pragma once

void Test_GetDiskFreeSpace(const std::wstring& rootPathName);
void Test_GetDiskFreeSpace_AllRootPath();
void Test_WriteFileAndGetDiskFreeSpace();
void Test_TruncateFileAndGetDiskFreeSpace();

inline void Test_GetDiskFreeSpaceAll()
{
    Test_GetDiskFreeSpace_AllRootPath();
    Test_WriteFileAndGetDiskFreeSpace();
    Test_TruncateFileAndGetDiskFreeSpace();
}