#include "stdafx.h"
#include "TestFindFirstChangeNotification.h"
#include "DirectoryManagement/ApiFindFirstChangeNotification.h"
#include <process.h>
#include "../File.h"

using namespace std;

UINT CreateOneFile(PVOID pParam)
{
    std::wstring* pFullName = (std::wstring*)pParam;
    
    File f(*pFullName, 0, 0, CREATE_ALWAYS);

    return 0;
}

void MonitorOneDirectory()
{
    DEF_TESTLOG_T("MonitorOneDirectory");
    std::wstring dirPath = GetTestFileName(L"dirPath");
    std::wstring fileName = GetTestFileName(L"fileName");
    std::wstring fullName = dirPath + L"\\" + fileName;

    if(!CreateDirectory(dirPath.c_str(), 0))
    {
        log.GetStream(TestLog::MT_ERROR) << L"DeleteFile error." << std::endl;
        return;
    }

    HANDLE hNotiObject = FindFirstChangeNotification(dirPath.c_str(), FALSE, 
        FILE_NOTIFY_CHANGE_SIZE | FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION );

    if(hNotiObject == 0)
    {
        RemoveDirectory(dirPath.c_str());
        return;
    }

    HANDLE hThread = chBEGINTHREADEX(0, 0, CreateOneFile, (PVOID)&fullName, 0, 0);

    DWORD dw = ::WaitForSingleObject(hThread, INFINITE);
    if(dw == WAIT_OBJECT_0)
    {
        dw = ::WaitForSingleObject(hNotiObject, 1);
        if(dw == WAIT_OBJECT_0)
        {
            //succ
            log.Ok();
        }
        else
        {
            log.GetStream(TestLog::MT_ERROR) << L"WaitForSingleObject error. Returned : " << dw << L", LastError : " << GetLastError() << std::endl;
        }
    }

    //DeleteFileOrCheck(log, fullName.c_str());
    //RemoveDirectory(dirPath.c_str());
}

