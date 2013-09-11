#include "stdafx.h"
#include "TestGetTempFileName.h"
#include "FileManagement/ApiGetTempFileName.h"
#include "FileManagement/ApiDeleteFile.h"

using namespace std;

void Test_GetTempFileName()
{
    DEF_TESTLOG_T("GetTempFileName, 현재 디렉토리에 대한 임시 파일을 생성해본다. differ에서 다르게 보일 수 있다.");

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