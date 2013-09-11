#include "stdafx.h"
#include "TestGetBinaryType.h"
#include "FileManagement/ApiGetBinaryType.h"

using namespace std;

/**
 - 실제로 Target에 EXE 파일하나를 복사한 뒤에 API를 테스트 함.
*/
void Test_GetBinaryType()
{
    DEF_TESTLOG_T("GetBinaryType, ");
    FixLater;
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
        log.GetStream(TestLog::MT_ERROR) << L"복사한 파일의 데이터가 일치하지 않습니다." << endl;
        return;
    }

    DWORD dwBinaryType;
    fOk = apiGetBinaryType(targetPath.c_str(), &dwBinaryType);

    if(fOk)
    {
        log.Ok();
    }
}