#pragma once

void Test_WriteFileAndSetFileTime();
void Test_SetFileTimeAndWriteFile();

inline void Test_WriteFileAll()
{
    Test_WriteFileAndSetFileTime();
    Test_SetFileTimeAndWriteFile();
}

