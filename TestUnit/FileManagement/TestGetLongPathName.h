#pragma once

void Test_GetLongPathName_DoesntExistFile();
void Test_GetLongPathName_Normal();
BOOL Test_GetLongPathName(TestLog& log, const std::wstring& sfilename, DWORD& lastError);


inline void Test_GetLongPathNameAll()
{
    Test_GetLongPathName_DoesntExistFile();
    Test_GetLongPathName_Normal();
}

