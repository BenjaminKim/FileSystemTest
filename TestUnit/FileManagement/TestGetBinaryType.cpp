#include "stdafx.h"
#include "TestGetBinaryType.h"
#include "FileManagement/ApiGetBinaryType.h"

using namespace std;

void Test_GetBinaryType()
{
    DEF_TESTLOG_T("GetBinaryType, ");
    FixLater;
    // TODO: This should be changed better way.
    wstring path = L"F:\\Downloads\\ctags58\\ctags58\\ctags.exe";

    std::wstring targetPath = GetWidTestBasePath() + L"ctags.exe";

    BOOL fOk = CopyFile(path.c_str(), targetPath.c_str(), FALSE);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to copy a file." << endl;
        return;
    }

    if(!AreBothOfFilesDataEqual(path.c_str(), targetPath.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Data not equal." << endl;
        return;
    }

    DWORD dwBinaryType;
    fOk = apiGetBinaryType(targetPath.c_str(), &dwBinaryType);

    if(fOk)
    {
        log.Ok();
    }
}