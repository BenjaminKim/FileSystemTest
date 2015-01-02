#include "stdafx.h"
#include "TestUtility.h"
#include <iostream>
#include <fstream>
#include "TestFileName.h"
#include <io.h>
#include "AllApi.h"
#include <process.h>
#include <stdlib.h>
#include "File.h"
#include <iterator>

using namespace std;

bool MakeFile(TestLog& log, const std::wstring& lpFileName)
{
    return MakeFile(log, lpFileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ);
}

bool MakeFile(TestLog& log, const std::wstring& lpFileName, size_t iFileSizeKB)
{
    return MakeFile(log, lpFileName.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, iFileSizeKB, 64);
}

bool MakeFile(TestLog& log, const std::wstring& lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode)
{
    return MakeFile(log, lpFileName, dwDesiredAccess, dwShareMode, 10, 64);
}

bool MakeFile(TestLog& log, const std::wstring& lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, size_t buffersizeKB)
{
    return MakeFile(log, lpFileName, dwDesiredAccess, dwShareMode, 10, buffersizeKB);
}

bool MakeFile(TestLog& log, const std::wstring& lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, size_t iFileSizeKB, size_t buffersizeKB)
{
    File f(lpFileName, dwDesiredAccess, dwShareMode, CREATE_ALWAYS);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
        return false;
    }

    if(buffersizeKB == 0)
    {
        buffersizeKB = 1;
    }
    
    char* buffer = new char[buffersizeKB * 1024];

    for(size_t i = 0; i < buffersizeKB; i++)
    {
        memcpy_s(buffer + (1024 * i), 1024, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "ABCDEFGHIJKLMNOPQRSTUV\r\n", 1024 );
    }

    DWORD writeBytes = 0;

    for(size_t x = 0; x < iFileSizeKB; x += buffersizeKB)
    {        
        if(uWriteFile(f, buffer, buffersizeKB * 1024, &writeBytes, 0) == FALSE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"WriteFile" << endl;
            delete[] buffer;
            return false;
        }

        if(writeBytes != buffersizeKB * 1024)
        {
            log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
            delete[] buffer;
            return false;
        }
    }

    delete[] buffer;

    log.GetStream(TestLog::MT_MESSAGE) << L"<" << lpFileName << L"> file created." << endl;
    return true;
}

bool DeleteFileOrCheck(TestLog& log, const std::wstring& lpFileName)
{
    SetFileAttributesW(lpFileName.c_str(), FILE_ATTRIBUTE_NORMAL);
    BOOL result = DeleteFileW(lpFileName.c_str());

    if(result)
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"Deletion success." << endl;
        return true;
    }

    if(GetLastError() == ERROR_FILE_NOT_FOUND)
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"Deletion success(file not found)." << endl;
        return true;
    }

    log.GetStream(TestLog::MT_ERROR) << L"<" << lpFileName << L"> file deletion." << endl;
    return false;
}

bool CheckFileData(TestLog& log, const std::wstring& lpFileName)
{
    return CheckFileData(log, lpFileName.c_str(), 10);
}

bool CheckFileData(TestLog& log, const std::wstring& lpFileName, INT32 iFileSizeKB)
{
    return CheckFileData(log, lpFileName.c_str(), iFileSizeKB, 64);
}

bool CheckFileData(TestLog& log, const std::wstring& lpFileName, INT32 iFileSizeKB, size_t buffersizeKB)
{
    File f(lpFileName, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
        return false;
    }

    if(buffersizeKB == 0)
    {
        buffersizeKB = 1;
    }

    char* buffer = new char[buffersizeKB * 1024];

    for(size_t i = 0; i < buffersizeKB; i++)
    {
        memcpy_s(buffer + (1024 * i), 1024, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
            "ABCDEFGHIJKLMNOPQRSTUV\r\n", 1024 );
    }

    char* readBuffer = new char[buffersizeKB * 1024];
    DWORD readBytes = 0;

    for(int x = 0; x < iFileSizeKB; x += buffersizeKB)
    {
        if(uReadFile(f, readBuffer, buffersizeKB * 1024, &readBytes, 0) == FALSE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ReadFile" << endl;
            delete[] readBuffer;
            delete[] buffer;
            return false;
        }
        if(readBytes != buffersizeKB * 1024)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ReadFile: readBytes Error." << endl;
            delete[] readBuffer;
            delete[] buffer;
            return false;
        }
        if(memcmp(readBuffer, buffer, buffersizeKB * 1024) != 0)
        {
            log.GetStream(TestLog::MT_ERROR) << L"memcmp" << endl;
            delete[] readBuffer;
            delete[] buffer;
            return false;
        }
    }

    delete[] readBuffer;
    delete[] buffer;

    log.GetStream(TestLog::MT_MESSAGE) << L"CheckFileData success." << endl;
    return true;
}

bool TouchFile(TestLog& log, LPCWSTR lpFileName)
{
    File f(lpFileName, GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, CREATE_ALWAYS);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
        return false;
    }

    log.GetStream(TestLog::MT_MESSAGE) << L"<" << lpFileName << L"> file created." << endl;
    return true;
}

bool TouchFile(TestLog& log, const std::wstring& filename)
{
    return TouchFile(log, filename.c_str());
}

std::wstring GetUniqueFileName(const std::wstring& parentDirPath)
{
    TCHAR sz[MAX_PATH] = { 0 };
    UINT iOk = uGetTempFileName(parentDirPath.c_str(), L"", 0, sz);

    if(iOk == 0)
    {
        return std::wstring(L"");
    }

    return std::wstring(sz);
}

bool EndOfThePathIsBackSlash(const std::wstring& path)
{
    return path[path.size() - 1] == L'\\' ? true : false;
}

std::wstring GetWidTestBasePath()
{
    TCHAR buf[MAX_PATH];

    DWORD dw = uGetCurrentDirectory(_countof(buf), buf);
    if(dw == 0)
    {
        return std::wstring(L"");
    }

    return std::wstring(buf);
}

/**
@brief 두 파일의 데이터가 완전히 일치하는지 체크
*/
bool AreBothOfFilesDataEqual(const std::wstring& path1, const std::wstring& path2)
{
    ifstream file1(path1.c_str(), ios::binary);
    ifstream file2(path2.c_str(), ios::binary);

    if(!file1 || !file2)
    {
        return false;
    }
    
    typedef istream_iterator<char> char_input;
    return equal(char_input(file1), char_input(), char_input(file2));
}

/**
@brief 파일을 임의의 데이터로 정해진 크기만큼 채운다.
사이즈가 정확히 안맞는 문제가 있으나 일단 패스.
*/
bool FillDummyData(const std::wstring& path, LONGLONG jSize)
{
    wofstream out(path.c_str());

    if(!out)
    {
        return false;
    }

    LONGLONG jWritten = 0;

    std::wstring dummyData(L"Hello World\n");

    while(jWritten + dummyData.size() < jSize)
    {
        out << dummyData;
        jWritten += dummyData.size();
    }

    if(jWritten < jSize)
    {
        for(int i = 0; i < jSize - jWritten - 1; ++i)
        {
            out << L".";
        }
    }

    return true;
}

BOOL IsFileExist(const std::wstring& strFullPath)
{
    WIN32_FIND_DATA FileData = { 0 };
    HANDLE hSearch = FindFirstFile(strFullPath.c_str(), &FileData);
    if(hSearch == INVALID_HANDLE_VALUE)
    {
        return FALSE;
    }
    FindClose(hSearch);

    return TRUE;
}

wstring GetCurrentModulePath()
{
    TCHAR sz[MAX_PATH] = { 0 };
    DWORD dw = GetModuleFileName(NULL, sz, MAX_PATH);
    
    if(dw == 0)
    {
        return wstring(L"");
    }

    return wstring(sz);
}

std::wstring FileTimeToString(FILETIME ft)
{
    SYSTEMTIME st;
    TCHAR szLocalDate[255] = { 0 };
    TCHAR szLocalTime[255] = { 0 };

    FileTimeToLocalFileTime(&ft, &ft);
    FileTimeToSystemTime(&ft, &st);
    GetDateFormat(LOCALE_SYSTEM_DEFAULT, DATE_LONGDATE, &st, NULL,
                  szLocalDate, 255);
    GetTimeFormat(LOCALE_SYSTEM_DEFAULT, 0, &st, NULL, szLocalTime, 255);

    return wstring(szLocalDate);// + _T(" ") + wstring(szLocalTime);
}

std::wstring FileSizeToString(DWORD nFileSizeHigh, DWORD nFileSizeLow)
{
    INT64 j = nFileSizeHigh;
    j <<= 32;
    j += nFileSizeLow;

    std::wostringstream oss;
    oss << j;
    return oss.str();
}

std::wstring IntegerToString(INT32 i)
{
    std::wostringstream oss;
    oss << i;
    return oss.str();
}

BOOL CreateDirectoryWithAttributes(TestLog& log, const std::wstring& path, DWORD dwAttribute)
{
    BOOL fOk = uCreateDirectory(path.c_str(), 0);

    log.GetStream(TestLog::MT_MESSAGE) << GetString_dwFileAttributes(dwAttribute) << std::endl;

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리 생성이 실패했습니다." << endl;
        return FALSE;
    }

    fOk = uSetFileAttributes(path.c_str(), dwAttribute);
    DWORD dwError = GetLastError();
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"디렉토리에 속성 값을 적용할 수 없습니다. " << GetErrorDefineString(dwError) << endl;
        return FALSE;
    }

    return TRUE;
}

BOOL IsVistaOrLater()
{
    OSVERSIONINFO osvi;

    osvi.dwOSVersionInfoSize = sizeof OSVERSIONINFO;

    //메이져 5 XP
    //메이져 6 VISTA
    if ( ::GetVersionEx( &osvi ) && 
        osvi.dwPlatformId == VER_PLATFORM_WIN32_NT && 
        (osvi.dwMajorVersion >= 6 ) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
};

std::wstring GetLastErrorStr()
{
    DWORD dwError = GetLastError();
    HLOCAL hlocal = NULL;

    BOOL fOk = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL, dwError, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL),
        (LPTSTR)&hlocal, 0, NULL);

    std::wstring lastErrorStr;
    if(fOk && (hlocal != NULL))
    {
        lastErrorStr = (wchar_t*)LocalLock(hlocal);
        LocalFree(hlocal);
    }

    return lastErrorStr;
}

BOOL TouchManyFiles(TestLog& log, size_t iFileNum, const std::wstring& basePath, std::vector<std::wstring>& vCreatedFiles, bool fDirectory)
{
    wstring predirectorypath;

    if(basePath.size() > 0)
    {
        predirectorypath = GetWidTestBasePath();

        // basePath가 존재하지 않으면 생성하는 코드 작성할 것
        // TODO
        if(!IsFileExist(basePath.c_str()))
        {
            CreateSubDir(basePath.c_str());
        }

        log.GetStream(TestLog::MT_MESSAGE) << L"Set Base path to : " << basePath << endl;
        BOOL fOk = uSetCurrentDirectory(basePath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            uSetCurrentDirectory(predirectorypath.c_str());
            return FALSE;
        }
    }

    if(vCreatedFiles.capacity() < iFileNum)
    {
        vCreatedFiles.reserve(iFileNum);
    }

    TestFileName t;

    wstring fileName = t.GetFirstFileName();
    if(fDirectory)
    {
        if(!uCreateDirectory(fileName.c_str(), 0))
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateDirectory Failed. : " << GetLastErrorStr() << endl;
            uSetCurrentDirectory(predirectorypath.c_str());
            return FALSE;
        }
    }
    else
    {
        if(!TouchFile(log, fileName))
        {
            log.GetStream(TestLog::MT_ERROR) << L"TouchFile Failed. : " << GetLastErrorStr() << endl;
            uSetCurrentDirectory(predirectorypath.c_str());
            return FALSE;
        }
    }    

    vCreatedFiles.push_back(fileName);

    for(size_t i = 1; i < iFileNum; ++i)
    {
        fileName = t.GetNextFileName();
        if(fDirectory)
        {
            if(!uCreateDirectory(fileName.c_str(), 0))
            {
                log.GetStream(TestLog::MT_ERROR) << L"CreateDirectory Failed. : " << GetLastErrorStr() << endl;
                uSetCurrentDirectory(predirectorypath.c_str());
                return FALSE;
            }
        }
        else
        {
            if(!TouchFile(log, fileName))
            {
                log.GetStream(TestLog::MT_ERROR) << L"TouchFile Failed. : " << GetLastErrorStr() << endl;
                uSetCurrentDirectory(predirectorypath.c_str());
                return FALSE;
            }
        }

        vCreatedFiles.push_back(fileName);
    }

    if(basePath.size() > 0 && predirectorypath.size() > 0)
    {
        BOOL fOk = uSetCurrentDirectory(predirectorypath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }
    }

    return TRUE;
}

void CreateSubDir(LPCTSTR lpszFileFullPath)
{
    std::wstring strDirect = _T("");
    int i = 0;
    TCHAR szPath[MAX_PATH] = { 0, };
    TCHAR szTemp[MAX_PATH] = { 0, };

    TCHAR* pNextToken = NULL;

    _tcscpy_s(szTemp, lpszFileFullPath);
    TCHAR* token;
    token = _tcstok_s(szTemp, _T("\\"), &pNextToken);
    while(token != NULL)
    {
        if(i == 0)
        {
            _stprintf_s(szPath, _T("%s"), token);
        }
        else
        {
            _stprintf_s(szPath, _T("%s\\%s"), szPath, token);
        }

        if( _taccess(szPath, 0) == -1 )
        {
            if(uCreateDirectory(szPath, NULL))
            {
                strDirect = szPath;
            }
        }
        else
        {
            strDirect = szPath;
        }
        token = _tcstok_s(NULL, _T("\\"), &pNextToken);
        i++;
    }
}

BOOL MakeManyFiles(TestLog& log, size_t iFileNum, INT32 iFileSize, const std::wstring& basePath, std::vector<std::wstring>& vCreatedFiles)
{
    wstring predirectorypath;

    if(basePath.size() > 0)
    {
        predirectorypath = GetWidTestBasePath();

        if(!IsFileExist(basePath.c_str()))
        {
            CreateSubDir(basePath.c_str());
        }

        log.GetStream(TestLog::MT_MESSAGE) << L"Set Base path to : " << basePath << endl;
        BOOL fOk = uSetCurrentDirectory(basePath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }
    }

    if(vCreatedFiles.capacity() < iFileNum)
    {
        vCreatedFiles.reserve(iFileNum);
    }

    TestFileName t;

    wstring fileName = t.GetFirstFileName();
    if(!MakeFile(log, fileName, iFileSize))
    {
        log.GetStream(TestLog::MT_ERROR) << L"TouchFile Failed. : " << GetLastErrorStr() << endl;
        return FALSE;
    }

    vCreatedFiles.push_back(fileName);

    for(size_t i = 0; i < iFileNum; ++i)
    {
        fileName = t.GetNextFileName();
        if(!MakeFile(log, fileName, iFileSize))
        {
            log.GetStream(TestLog::MT_ERROR) << L"TouchFile Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }

        vCreatedFiles.push_back(fileName);
    }

    if(basePath.size() > 0 && predirectorypath.size() > 0)
    {
        BOOL fOk = uSetCurrentDirectory(predirectorypath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }
    }

    return TRUE;
}

BOOL TouchManyFilesConcurrently(TestLog& log, size_t iFileNum, const std::wstring& basePath, std::vector<std::wstring>& vCreatedFiles)
{
    wstring predirectorypath;

    if(basePath.size() > 0)
    {
        predirectorypath = GetWidTestBasePath();

        if(!IsFileExist(basePath.c_str()))
        {
            CreateSubDir(basePath.c_str());
        }

        log.GetStream(TestLog::MT_MESSAGE) << L"Set Base path to : " << basePath << endl;
        BOOL fOk = uSetCurrentDirectory(basePath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }
    }

    if(vCreatedFiles.capacity() < iFileNum)
    {
        vCreatedFiles.reserve(iFileNum);
    }

    TestFileName t;

    wstring fileName = t.GetFirstFileName();
    vCreatedFiles.push_back(fileName);

    for(size_t i = 0; i < iFileNum; ++i)
    {
        fileName = t.GetNextFileName();
        vCreatedFiles.push_back(fileName);
    }   

    if(basePath.size() > 0 && predirectorypath.size() > 0)
    {
        BOOL fOk = uSetCurrentDirectory(predirectorypath.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Current Directory Setting Failed. : " << GetLastErrorStr() << endl;
            return FALSE;
        }
    }

    return TRUE;
}

void OpenMSWord(size_t n)
{
    for(size_t i = 0; i < n; ++i)
    {
        SHELLEXECUTEINFO si;
        memset( (void *)&si, 0, sizeof( SHELLEXECUTEINFO ) );

        si.cbSize = sizeof( SHELLEXECUTEINFO );
        si.lpVerb = _T("Open");
        si.lpFile = _T("winword");
        si.nShow = SW_SHOW;
        si.lpParameters = _T("\"F:\\Documents\\Up.docx\" / ");
        si.fMask = SEE_MASK_NOCLOSEPROCESS|SEE_MASK_NOASYNC;

        BOOL fOk = ShellExecuteEx( &si );

        if ( !fOk )
        {
            wcout << L"error" << endl;
        }
    }
}

std::wstring GetSrcFileName()
{
    std::wostringstream oss;
    oss << L"Case" << TestLog::CaseN() << L"src";

    return oss.str();
}

std::wstring GetDstFileName()
{
    std::wostringstream oss;
    oss << L"Case" << TestLog::CaseN() << L"dst";

    return oss.str();
}

std::wstring GetTestFileName()
{
    std::wostringstream oss;
    oss << L"Case" << TestLog::CaseN() << L"test";

    return oss.str();
}

std::wstring GetTestFileName(const std::wstring& filename)
{
    std::wostringstream oss;
    oss << L"Case" << TestLog::CaseN() << L"_" << filename;

    return oss.str();
}

bool IsTimeToEnd()
{
    if(!TestLog::fUseTimer_)
    {
        return false;
    }

    SYSTEMTIME c;
    GetLocalTime(&c);

    if(c.wHour > TestLog::endtime_.wHour)
    {
        return true;
    }
    else if(c.wHour < TestLog::endtime_.wHour)
    {
        return false;
    }
    else if(c.wMinute > TestLog::endtime_.wMinute)
    {
        return true;
    }
    else if(c.wMinute < TestLog::endtime_.wMinute)
    {
        return false;
    }
    else
    {
        return c.wSecond >= TestLog::endtime_.wSecond;
    }
}

bool IsTimeToStart()
{
    if(!TestLog::fUseTimer_)
    {
        return true;
    }

    SYSTEMTIME c;
    GetLocalTime(&c);

    if(c.wMinute < TestLog::starttime_.wMinute)
    {
        return false;
    }
    else if(c.wMinute > TestLog::starttime_.wMinute)
    {
        return true;
    }
    else
    {
        return c.wSecond >= TestLog::starttime_.wSecond;
    }
}

void WaitUntilStartTime()
{
    if(!TestLog::fUseTimer_)
    {
        return;
    }

    while(!IsTimeToStart())
    {
        SYSTEMTIME c;
        GetLocalTime(&c);

        wcout << c.wMinute << L":" << c.wSecond << endl;
        Sleep(1000);
    }
}