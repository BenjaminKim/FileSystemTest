#include "stdafx.h"
#include "TestCreateFileMapping.h"
#include "../File.h"
#include "FileIO/ApiCreateFileMapping.h"

using namespace std;

void Test_CreateFileMapping_ReverseFile()
{
    DEF_TESTLOG_T("Test_CreateFileMapping_ReverseFile");

    wstring fileName = GetTestFileName(L"Test_CreateFileMapping_ReverseFile");

    if(!MakeFile(log, fileName, 64))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file." << endl;
        return;
    }

    BOOL fUnicode = TRUE;
    BOOL fOk = FileReverse(log, fileName.c_str(), &fUnicode);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to reverse a file." << endl;
        return;
    }

    uDeleteFile(fileName.c_str());

    log.Ok();
}

void Test_CreateFileMapping_Basic()
{
    DEF_TESTLOG_T("Test_CreateFileMapping_Basic");

    wstring fileName = GetTestFileName(L"Test_CreateFileMapping_Basic");

    if(!MakeFile(log, fileName, 64))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file." << endl;
        return;
    }

    File f(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE);

    // 4G + 1Byte
    HANDLE hFileMapping = apiCreateFileMapping(f, NULL, PAGE_READWRITE, 0x0 /*4Gb*/, 512*1024/*1 Byte*/, 0);

    if(!hFileMapping)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a section object." << endl;
        f.CloseHandle();
        uDeleteFile(fileName.c_str());
        return;
    }

    //bool fOk = CheckFileData(log, fileName, 64);
    PBYTE pbFile = (PBYTE)MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, 0);

    if(pbFile)
        pbFile[0] = '!';

    std::vector<char> buf;
    buf.resize(512*1024);

    for(size_t i = 0; i < buf.size(); ++i)
    {
        *&buf[i] = 'A';
    }

    memcpy_s(pbFile, 512*1024, &buf[0], buf.size());

    UnmapViewOfFile(pbFile); // Flush occurs here.
    CloseHandle(hFileMapping);

    f.CloseHandle();
    uDeleteFile(fileName.c_str());

    log.Ok();
}

BOOL FileReverse(TestLog& log, PCTSTR pszPathname, PBOOL pbIsTextUnicode)
{
    *pbIsTextUnicode = FALSE;  // Assume text is Unicode

    // Open the file for reading and writing.
    HANDLE hFile = CreateFile(pszPathname, GENERIC_WRITE | GENERIC_READ, 0, 
        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        log.GetStream(TestLog::MT_ERROR) << L"File could not be opened.";
        return(FALSE);
    }

    // Get the size of the file (I assume the whole file can be mapped).
    DWORD dwFileSize = GetFileSize(hFile, NULL);

    // Create the file-mapping object. The file-mapping object is 1 character 
    // bigger than the file size so that a zero character can be placed at the 
    // end of the file to terminate the string (file). Because I don't yet know
    // if the file contains ANSI or Unicode characters, I assume worst case
    // and add the size of a WCHAR instead of CHAR.
    HANDLE hFileMap = apiCreateFileMapping(hFile, NULL, PAGE_READWRITE, 
        0, dwFileSize + sizeof(WCHAR), NULL);

    if (hFileMap == NULL) {
        log.GetStream(TestLog::MT_ERROR) << L"File map could not be opened.";
        CloseHandle(hFile);
        return(FALSE);
    }

    // Get the address where the first byte of the file is mapped into memory.
    PVOID pvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

    if (pvFile == NULL) {
        log.GetStream(TestLog::MT_ERROR) << L"Could not map view of file.";
        CloseHandle(hFileMap);
        CloseHandle(hFile);
        return(FALSE);
    }

    // Does the buffer contain ANSI or Unicode?
    int iUnicodeTestFlags = -1;   // Try all tests
    *pbIsTextUnicode = IsTextUnicode(pvFile, dwFileSize, &iUnicodeTestFlags);

    if (!*pbIsTextUnicode) {
        // For all the file manipulations below, we explicitly use ANSI 
        // functions because we are processing an ANSI file.

        // Put a zero character at the very end of the file.
        PSTR pchANSI = (PSTR) pvFile;
        pchANSI[dwFileSize / sizeof(CHAR)] = 0;

        // Reverse the contents of the file.
        _strrev(pchANSI);

        // Convert all "\n\r" combinations back to "\r\n" to 
        // preserve the normal end-of-line sequence.
        pchANSI = strstr(pchANSI, "\n\r"); // Find first "\r\n".

        while (pchANSI != NULL) {
            // We have found an occurrence....
            *pchANSI++ = '\r';   // Change '\n' to '\r'.
            *pchANSI++ = '\n';   // Change '\r' to '\n'.
            pchANSI = strstr(pchANSI, "\n\r"); // Find the next occurrence.
        }

    } else {
        // For all the file manipulations below, we explicitly use Unicode
        // functions because we are processing a Unicode file.

        // Put a zero character at the very end of the file.
        PWSTR pchUnicode = (PWSTR) pvFile;
        pchUnicode[dwFileSize / sizeof(WCHAR)] = 0;

        if ((iUnicodeTestFlags & IS_TEXT_UNICODE_SIGNATURE) != 0) {
            // If the first character is the Unicode BOM (byte-order-mark), 
            // 0xFEFF, keep this character at the beginning of the file.
            pchUnicode++;
        }

        // Reverse the contents of the file.
        _wcsrev(pchUnicode);

        // Convert all "\n\r" combinations back to "\r\n" to 
        // preserve the normal end-of-line sequence.
        pchUnicode = wcsstr(pchUnicode, L"\n\r"); // Find first '\n\r'.

        while (pchUnicode != NULL) {
            // We have found an occurrence....
            *pchUnicode++ = L'\r';   // Change '\n' to '\r'.
            *pchUnicode++ = L'\n';   // Change '\r' to '\n'.
            pchUnicode = wcsstr(pchUnicode, L"\n\r"); // Find the next occurrence.
        }
    }

    // Clean up everything before exiting.
    UnmapViewOfFile(pvFile);
    CloseHandle(hFileMap);

    // Remove trailing zero character added earlier.
    SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
    SetEndOfFile(hFile);
    CloseHandle(hFile);

    return(TRUE);
}