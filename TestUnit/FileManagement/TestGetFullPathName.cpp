#include "stdafx.h"
#include "TestGetFullPathName.h"
#include "FileManagement/ApiGetFullPathName.h"
#include "../File.h"

using namespace std;

void Test_GetFullPathName()
{
    DEF_TESTLOG_T("GetFullPathName.");
    std::wstring fileName = GetTestFileName();
    {
        File f(fileName, GENERIC_READ, FILE_SHARE_READ, OPEN_ALWAYS);
        
        TCHAR buf[MAX_PATH] = { 0 };
        TCHAR** lppPart={NULL}; // 이런 변수를 만드는 것은 이상하다.

        if(!f.IsValidHandle())
        {
            return;
        }

        apiGetFullPathName(fileName.c_str(), MAX_PATH, buf, lppPart);
    }

    uDeleteFile(fileName.c_str());
    
    log.Ok();
}