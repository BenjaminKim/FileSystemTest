#include "stdafx.h"
#include "TestGetFileType.h"
#include "FileManagement/ApiGetFileType.h"
#include "../File.h"

using namespace std;

void Test_GetFileType()
{
    DEF_TESTLOG_T("GetFileType, 파일 타입을 구한다.");
    std::wstring fileName = GetTestFileName(L"GetFileType");

    File f(fileName, GENERIC_READ, FILE_SHARE_READ, OPEN_ALWAYS);
    
    if(!f.IsValidHandle())
    {
        return;
    }

    apiGetFileType(f);

    f.CloseHandle();

    uDeleteFile(fileName.c_str());
    
    log.Ok();
}