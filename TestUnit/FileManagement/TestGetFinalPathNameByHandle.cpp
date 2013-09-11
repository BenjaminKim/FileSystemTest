#include "stdafx.h"
#include "TestGetFinalPathNameByHandle.h"
#include "FileManagement/ApiGetFinalPathNameByHandle.h"
#include "FileManagement/ApiSetFileAttributes.h"
#include "../File.h"
#include "FileManagement/ApiDeleteFile.h"

using namespace std;
//Windows vista
void Test_GetFinalPathNameByHandleAll()
{
    Test_GetFinalPathNameByHandle(FILE_NAME_NORMALIZED | VOLUME_NAME_DOS);
    Test_GetFinalPathNameByHandle(FILE_NAME_NORMALIZED | VOLUME_NAME_GUID);
    Test_GetFinalPathNameByHandle(FILE_NAME_NORMALIZED | VOLUME_NAME_NONE);
    Test_GetFinalPathNameByHandle(FILE_NAME_NORMALIZED | VOLUME_NAME_NT);

    Test_GetFinalPathNameByHandle(FILE_NAME_OPENED | VOLUME_NAME_DOS);
    Test_GetFinalPathNameByHandle(FILE_NAME_OPENED | VOLUME_NAME_GUID);
    Test_GetFinalPathNameByHandle(FILE_NAME_OPENED | VOLUME_NAME_NONE);
    Test_GetFinalPathNameByHandle(FILE_NAME_OPENED | VOLUME_NAME_NT);

    MSG(심볼릭 링크 테스트도 케이스에 집어 넣을 것);
}

void Test_GetFinalPathNameByHandle(DWORD dwFlags)
{
    DEF_TESTLOG_T("GetFinalPathNameByHandle");

    if(!IsVistaOrLater())
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"Supported at vista or later version." << endl;
        return;
    }

    std::wstring fileName(_T("FinalPathNameByHandle"));
    TouchFile(log, fileName);
    File f(fileName);
    
    TCHAR sz[MAX_PATH] = { 0 };
    DWORD dw = apiGetFinalPathNameByHandle((HANDLE)f, sz, _countof(sz), dwFlags);

    f.CloseHandle();

    if(dw == 0 || dw > _countof(sz))
    {
        log.GetStream(TestLog::MT_ERROR) << L"GetFinalPathNameByHandle Api에서 오류가 발생했습니다(" << GetLastErrorStr() << L")" << endl;

        f.CloseHandle();
        BOOL fOk = uDeleteFile(fileName.c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제하지 못했습니다." << endl;
            return;
        }

        return;
    }
    
    f.CloseHandle();
    BOOL fOk = uDeleteFile(fileName.c_str());
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일을 삭제하지 못했습니다." << endl;
        return;
    }

    log.Ok();
}