#pragma once

void Test_CreateFile_NewFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition);
void Test_CreateFile_NewFileAccessAllDisposition(DWORD dwDesiredAccess);
void Test_CreateFile_NewFileAccessDisposition();
void Test_CreateFile_ExistingFile(DWORD dwDesiredAccess, DWORD dwCreateDisposition);
void Test_CreateFile_ExistingFileAccessAllDisposition(DWORD dwDesiredAccess);
void Test_CreateFile_ExistingFileAccessDisposition();
void Test_CreateFile_OpenDeletePendingFile();
void Test_CreateFile_OpenDirectory();

inline void Test_CreateFile_All()
{
    Test_CreateFile_NewFileAccessDisposition();
    Test_CreateFile_ExistingFileAccessDisposition();
    //Test_CreateFile_OpenDeletePendingFile();
    Test_CreateFile_OpenDirectory();
}
