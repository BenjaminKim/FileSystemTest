#include "stdafx.h"
#include "TestFindFirstFileNameW.h"
#include "FileManagement/ApiFindFirstFileNameW.h"
#include "FileManagement/ApiDeleteFile.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"

using namespace std;

/**
@breif Windows Vistar supported.
*/
void Test_FindFirstFileNameW()
{
    DEF_TESTLOG_T("FindFirstFileNameW, ");

    if(!IsVistaOrLater())
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"Supported at vista or later version." << endl;
        return;
    }    

    vector<wstring> v;
    BOOL fOk = TouchManyFiles(log, 100, GetWidTestBasePath() + L"\\ManyFiles\\", v, false);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성이 실패했습니다." << endl;
        return;
    }

    for(size_t i = 0; i < v.size(); ++i)
    {        
        wstring fileName = (GetWidTestBasePath() + L"\\ManyFiles\\" + v[i]).c_str();

        WCHAR pchLinkName[MAX_PATH] = { 0 };
        DWORD dwStringLength = _countof(pchLinkName);
        apiFindFirstFileNameW(fileName.c_str(), 0, &dwStringLength, pchLinkName);

        fOk = uDeleteFile(fileName.c_str());

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"파일 삭제가 실패했습니다." << endl;
            return;
        }
    }

    uRemoveDirectory((GetWidTestBasePath() + L"\\ManyFiles").c_str());
   
    log.Ok();
}