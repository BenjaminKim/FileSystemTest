#pragma once

void Test_FindFirstFile_ManyFiles_With_Wildcard(size_t fileNum);
void Test_FindFirstFile_ManyFiles_With_NoWildcard(size_t fileNum);
void Test_FindFirstFile_DeletePending();
void Test_FindFirstFile_CreateManyFiles_And_Listring_With_Wildcard(size_t fileNum, size_t listCount);
void Test_FindFirstFile_Directory_With_Wildcard(size_t dirNum);
void Test_FindFirstFile_Directory_With_NoWildcard(size_t dirNum);

inline void Test_FindFirstFile_All()
{
    Test_FindFirstFile_ManyFiles_With_Wildcard(10);
    Test_FindFirstFile_ManyFiles_With_NoWildcard(10);
    Test_FindFirstFile_DeletePending();
    Test_FindFirstFile_Directory_With_Wildcard(10);
    Test_FindFirstFile_Directory_With_NoWildcard(10);
}