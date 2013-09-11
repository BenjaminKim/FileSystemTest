#pragma once

void Test_GetFileSizeEx();
void Test_WriteAndGetFileSize();
void Test_WriteAndGetFileSize2();

inline void Test_GetFileSizeExAll()
{
    Test_GetFileSizeEx();
    Test_WriteAndGetFileSize();
    Test_WriteAndGetFileSize2();
}