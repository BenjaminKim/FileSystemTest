#pragma once

void Test_CreateFileMapping_ReverseFile();
void Test_CreateFileMapping_Basic();
BOOL FileReverse(TestLog& log, PCTSTR pszPathname, PBOOL pbIsTextUnicode);

inline void Test_CreateFileMapping_All()
{
    Test_CreateFileMapping_ReverseFile();
    Test_CreateFileMapping_Basic();
}