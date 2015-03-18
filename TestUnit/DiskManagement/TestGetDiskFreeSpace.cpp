#include "stdafx.h"
#include "TestGetDiskFreeSpace.h"
#include "DiskManagement/ApiGetDiskFreeSpace.h"
#include "../File.h"
#include "FileIO/ApiSetEndOfFile.h"
#include "FileIO/ApiSetFilePointer.h"
#include "FileIO/ApiSetFilePointerEx.h"
#include "FileManagement/ApiGetFileSizeEx.h"
#include "FileIO/ApiWriteFile.h"

using namespace std;

void Test_GetDiskFreeSpace(const std::wstring& rootPathName)
{
    DEF_TESTLOG_T("GetDiskFreeSpace");

    DWORD dwSectorsPerCluster;
    DWORD dwBytesPerSector;
    DWORD dwNumberOfFreeClusters;
    DWORD dwTotalNumberOfClusters;

    if(!apiGetDiskFreeSpace(rootPathName.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    log.Ok();
}

void Test_WriteFileAndGetDiskFreeSpace()
{
    DEF_TESTLOG_T("Test_WriteFileAndGetDiskFreeSpace : Check disk free space after WriteFile.");

    wstring fileName = GetTestFileName();
    BOOL fOk = MakeFile(log, fileName);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
    }

    DWORD dwSectorsPerCluster;
    DWORD dwBytesPerSector;
    DWORD dwNumberOfFreeClusters;
    DWORD dwTotalNumberOfClusters;

    WCHAR CurrentDirectory[MAX_PATH];
    if(GetCurrentDirectory(_countof(CurrentDirectory), CurrentDirectory) == 0)
    {
        return;
    }

    std::wstring sCurrentDir = std::wstring(CurrentDirectory).substr(0, 3);

    File f1(fileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, OPEN_EXISTING);
    
    if(!apiGetDiskFreeSpace(sCurrentDir.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    INT64 jOriginFreeSpace = dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters;

    {
        File f2(fileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, OPEN_EXISTING);

        BYTE buf[500*1024] = { 'A', };
        DWORD BytesWritten = 0;
        for(size_t i = 0; i < 100; ++i)
        {
            if(!apiWriteFile(f2, buf, sizeof(buf), &BytesWritten, 0))
            {
                log.GetStream(TestLog::MT_ERROR) << L"WriteFile failed" << endl;
            }
        }

        LARGE_INTEGER li;
        apiGetFileSizeEx(f2, &li);
    }

    Sleep(5000); // Remove cache

    if(!apiGetDiskFreeSpace(sCurrentDir.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    INT64 jAfterFreeSpace = dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters;

    log.GetStream(TestLog::MT_MESSAGE) << L"Diff Free Space : " << jOriginFreeSpace - jAfterFreeSpace << endl;

    File f2(fileName);
    LARGE_INTEGER li2;
    apiGetFileSizeEx(f2, &li2);
    f2.CloseHandle();
    apiGetFileSizeEx(f1, &li2);
    f1.CloseHandle();
    if(!apiGetDiskFreeSpace(sCurrentDir.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }

    log.Ok();
}

void Test_TruncateFileAndGetDiskFreeSpace()
{
    DEF_TESTLOG_T("Test_TruncateFileAndGetDiskFreeSpace : Check disk free space after truncating a file.");

    wstring fileName = GetTestFileName();
    BOOL fOk = MakeFile(log, fileName);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
    }

    DWORD dwSectorsPerCluster;
    DWORD dwBytesPerSector;
    DWORD dwNumberOfFreeClusters;
    DWORD dwTotalNumberOfClusters;

    WCHAR CurrentDirectory[MAX_PATH];
    if(GetCurrentDirectory(_countof(CurrentDirectory), CurrentDirectory) == 0)
    {
        return;
    }

    std::wstring sCurrentDir = std::wstring(CurrentDirectory).substr(0, 3);


    if(!apiGetDiskFreeSpace(sCurrentDir.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    INT64 jOriginFreeSpace = dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters;

    {
        File f(fileName, GENERIC_WRITE, 0, CREATE_ALWAYS);

        LARGE_INTEGER li;
        li.QuadPart = 1*1024*1024*1024;
        fOk = apiSetFilePointerEx(f, li, 0, FILE_END);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetFilePointerEx Failed." << endl;
        }

        fOk = apiSetEndOfFile(f);

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"ApiSetEndOfFile Failed." << endl;
        }

        apiGetFileSizeEx(f, &li);
    }

    Sleep(5000);

    if(!apiGetDiskFreeSpace(sCurrentDir.c_str(), &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters))
    {
        return;
    }

    INT64 jAfterFreeSpace = dwSectorsPerCluster * dwBytesPerSector * dwNumberOfFreeClusters;

    log.GetStream(TestLog::MT_MESSAGE) << L"Diff Free Space : " << jOriginFreeSpace - jAfterFreeSpace << endl;

    File f2(fileName);
    LARGE_INTEGER li2;
    apiGetFileSizeEx(f2, &li2);
    f2.CloseHandle();

    fOk = uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file." << endl;
        return;
    }

    log.Ok();
}