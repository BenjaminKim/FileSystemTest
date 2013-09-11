#pragma once

void Test_MoveDirectory_Normal();
void Test_MoveDirectory_NoExistingSrc();
void Test_MoveDirectory_ExistingDst();
void Test_MoveDirirectory_WithOpenedSubFiles();

inline void Test_MoveDirectory_All()
{
    Test_MoveDirectory_Normal();
    Test_MoveDirectory_NoExistingSrc();
    Test_MoveDirectory_ExistingDst();
    Test_MoveDirirectory_WithOpenedSubFiles();
}