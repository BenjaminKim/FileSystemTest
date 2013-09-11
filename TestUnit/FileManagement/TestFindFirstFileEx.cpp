#include "stdafx.h"
#include "TestFindFirstFileEx.h"
#include "FileManagement/ApiFindFirstFileEx.h"

using namespace std;

void Test_FindFirstFileEx_All()
{
    Test_FindFirstFileEx_With_WildCard(FindExInfoStandard, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_WildCard(FindExInfoStandard, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_WildCard(FindExInfoStandard, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);

    Test_FindFirstFileEx_With_WildCard(FindExInfoMaxInfoLevel, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_WildCard(FindExInfoMaxInfoLevel, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_WildCard(FindExInfoMaxInfoLevel, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);



    Test_FindFirstFileEx_With_Question(FindExInfoStandard, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_Question(FindExInfoStandard, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_Question(FindExInfoStandard, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);

    Test_FindFirstFileEx_With_Question(FindExInfoMaxInfoLevel, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_Question(FindExInfoMaxInfoLevel, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_Question(FindExInfoMaxInfoLevel, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);



    Test_FindFirstFileEx_With_NoWildCard(FindExInfoStandard, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_NoWildCard(FindExInfoStandard, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_NoWildCard(FindExInfoStandard, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);

    Test_FindFirstFileEx_With_NoWildCard(FindExInfoMaxInfoLevel, FindExSearchNameMatch, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_NoWildCard(FindExInfoMaxInfoLevel, FindExSearchLimitToDirectories, FIND_FIRST_EX_CASE_SENSITIVE);
    Test_FindFirstFileEx_With_NoWildCard(FindExInfoMaxInfoLevel, FindExSearchLimitToDevices, FIND_FIRST_EX_CASE_SENSITIVE);
}

void Test_FindFirstFileEx_With_WildCard(FINDEX_INFO_LEVELS fInfoLevelId, FINDEX_SEARCH_OPS fSearchOp, DWORD dwAdditionalFlags)
{
    DEF_TESTLOG_T("Test_FindFirstFileEx_With_WildCard, 파일의 첫번째 바이트를 *로 해서 탐색");

    wstring fileName = GetTestFileName(L"Test_FindFirstFileEx_With_WildCard");

    if(!MakeFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    _tprintf (TEXT("Target file is %s\n"), (L"*" + fileName.substr(1)).c_str());
    hFind = FindFirstFileEx((L"*" + fileName.substr(1)).c_str(), fInfoLevelId, &FindFileData,
        fSearchOp, NULL, dwAdditionalFlags);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        log.GetStream(TestLog::MT_ERROR) << L"FindFirstFileEx failed " << GetLastError() << GetLastErrorStr() << endl;
        DeleteFile(fileName.c_str());
        return;
    } 
    else 
    {
        _tprintf (TEXT("The first file found is %s\n"), 
            FindFileData.cFileName);
        FindClose(hFind);
    }

    DeleteFile(fileName.c_str());

    log.Ok();
}

void Test_FindFirstFileEx_With_Question(FINDEX_INFO_LEVELS fInfoLevelId, FINDEX_SEARCH_OPS fSearchOp, DWORD dwAdditionalFlags)
{
    DEF_TESTLOG_T("Test_FindFirstFileEx_With_Question, 파일의 첫번째 바이트를 ?로 해서 탐색");

    wstring fileName = GetTestFileName(L"Test_FindFirstFileEx_With_Question");

    if(!MakeFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    _tprintf (TEXT("Target file is %s\n"), (L"?" + fileName.substr(1)).c_str());
    hFind = FindFirstFileEx((L"?" + fileName.substr(1)).c_str(), fInfoLevelId, &FindFileData,
        fSearchOp, NULL, dwAdditionalFlags);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        log.GetStream(TestLog::MT_ERROR) << L"FindFirstFileEx failed " << GetLastError() << GetLastErrorStr() << endl;
        DeleteFile(fileName.c_str());
        return;
    } 
    else 
    {
        _tprintf (TEXT("The first file found is %s\n"), 
            FindFileData.cFileName);
        FindClose(hFind);
    }

    DeleteFile(fileName.c_str());

    log.Ok();
}

void Test_FindFirstFileEx_With_NoWildCard(FINDEX_INFO_LEVELS fInfoLevelId, FINDEX_SEARCH_OPS fSearchOp, DWORD dwAdditionalFlags)
{
    DEF_TESTLOG_T("Test_FindFirstFileEx_With_NoWildCard, ");

    wstring fileName = GetTestFileName(L"Test_FindFirstFileEx_With_NoWildCard");

    if(!MakeFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"파일 생성에 실패했습니다." << endl;
        return;
    }

    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;

    _tprintf (TEXT("Target file is %s\n"), fileName.c_str());
    hFind = FindFirstFileEx(fileName.c_str(), fInfoLevelId, &FindFileData,
        fSearchOp, NULL, dwAdditionalFlags);
    if (hFind == INVALID_HANDLE_VALUE) 
    {
        log.GetStream(TestLog::MT_ERROR) << L"FindFirstFileEx failed " << GetLastError() << GetLastErrorStr() << endl;
        DeleteFile(fileName.c_str());
        return;
    } 
    else 
    {
        _tprintf (TEXT("The first file found is %s\n"), 
            FindFileData.cFileName);
        FindClose(hFind);
    }

    DeleteFile(fileName.c_str());

    log.Ok();
}