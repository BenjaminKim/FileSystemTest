#include "stdafx.h"
#include "TestGetTempFileName.h"
#include "FileManagement/ApiGetTempFileName.h"
#include "FileManagement/ApiDeleteFile.h"

using namespace std;

void Test_GetTempFileName()
{
    DEF_TESTLOG_T("GetTempFileName, Trying to create temporary file for current directory. This might ruin view of diff tool.");

    TCHAR t[MAX_PATH];
    UINT uSucceed = apiGetTempFileName(GetWidTestBasePath().c_str(), L"PRE", 0, t);

    if(uSucceed > 0)
    {
        BOOL fOk = uDeleteFile(t);
        if(!fOk)
        {
            std::wcout << L"Can not delete the file";
            return;
        }
    }
    else
    {
        std::wcout << L"GetTempFileName function is failed.";
        return;
    }
    
    log.Ok();
}