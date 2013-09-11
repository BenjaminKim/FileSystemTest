#include "stdafx.h"
#include "TestGetBinaryType.h"
#include "FileManagement/ApiGetBinaryType.h"

using namespace std;

/**
 - ������ Target�� EXE �����ϳ��� ������ �ڿ� API�� �׽�Ʈ ��.
*/
void Test_GetBinaryType()
{
    DEF_TESTLOG_T("GetBinaryType, ");
    wstring path = L"F:\\Downloads\\ctags58\\ctags58\\ctags.exe";

    std::wstring targetPath = GetWidTestBasePath() + L"ctags.exe";

    BOOL fOk = CopyFile(path.c_str(), targetPath.c_str(), FALSE);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"���� ���翡 �����߽��ϴ�." << endl;
        return;
    }

    if(!AreBothOfFilesDataEqual(path.c_str(), targetPath.c_str()))
    {
        log.GetStream(TestLog::MT_ERROR) << L"������ ������ �����Ͱ� ��ġ���� �ʽ��ϴ�." << endl;
        return;
    }

    DWORD dwBinaryType;
    fOk = apiGetBinaryType(targetPath.c_str(), &dwBinaryType);

    if(fOk)
    {
        log.Ok();
    }
}