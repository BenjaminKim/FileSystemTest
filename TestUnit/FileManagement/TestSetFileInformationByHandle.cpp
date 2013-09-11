#include "stdafx.h"
#include "TestSetFileInformationByHandle.h"
#include "FileManagement/ApiSetFileInformationByHandle.h"
#include "TestUnit/TestUtility.h"
#include "../File.h"

using namespace std;
//Windows vista
void Test_SetFileInformationByHandleAll()
{
    if(!IsVistaOrLater())
    {
        return;
    }

    Test_SetFileInformationByHandle_Disposition_NormalFile();
    Test_SetFileInformationByHandle_Disposition_ReadOnlyFile1();
    Test_SetFileInformationByHandle_Disposition_ReadOnlyFile2();
    Test_SetFileInformationByHandle_Delete_Twice();
    Test_SetFileInformationByHandle_Delete_No_Have_Delete_DesireAccess();
    Test_SetFileInformationByHandle_FileTimeAll();
}

static void Test_SetFileInformationByHandle_Disposition_NormalFile()
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_Disposition_NormalFile 테스트");

    std::wstring fileName = GetTestFileName();
    BOOL fOk;
    BOOL failed = FALSE;

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastErrorStr() << endl;
        failed = TRUE;
    }

    while(failed == FALSE)
    {
        File f1(fileName,
            GENERIC_READ | GENERIC_WRITE | DELETE,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

        FILE_DISPOSITION_INFO dispositionInfo;

        dispositionInfo.DeleteFile = TRUE;

        fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

        if(fOk)
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"파일이 삭제 상태로 마킹됨." << endl;
        }
        else
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"apiSetFileInformationByHandle가 실패했습니다." << endl;
            failed = TRUE;
            break;
        }

        // 파일을 열어본다.(파일이 삭제되어 있어야 함)
        {
            HANDLE h = apiCreateFile(fileName.c_str(),
                GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
            if(h != INVALID_HANDLE_VALUE)
            {
                log.GetStream(TestLog::MT_ERROR) << L"SetFileInformation 오작동." << endl;
                failed = TRUE;
                CloseHandle(h);
            }
        }

        dispositionInfo.DeleteFile = FALSE;

        fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) <<
                L"apiSetFileInformationByHandle가 실패했습니다." << endl;
            failed = TRUE;
            break;
        }

        // 파일을 또 열어본다.(파일이 삭제되지 않고 정상적으로 있어야 함)
        {
            HANDLE h = apiCreateFile(fileName.c_str(),
                GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
            if(h != INVALID_HANDLE_VALUE)
            {
                CloseHandle(h);
            }
            else
            {
                log.GetStream(TestLog::MT_ERROR) << L"SetFileInformation 오작동." << endl;
                failed = TRUE;
            }
        }
        break;
    }

    // 파일을 열어본다. (파일이 정상적으로 있어야 함)
    {
        HANDLE h = apiCreateFile(fileName.c_str(),
            GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if(h != INVALID_HANDLE_VALUE)
        {
            CloseHandle(h);
            log.GetStream(TestLog::MT_MESSAGE) << L"파일이 정상적으로 복구되었음." << endl;
        }
        else
        {
            log.GetStream(TestLog::MT_ERROR) << L"SetFileInformation 오작동." << endl;
            failed = TRUE;
        }
    }

    DeleteFileOrCheck(log, fileName);

    if(failed == FALSE)
    {
        log.Ok();
    }
}

static void Test_SetFileInformationByHandle_Disposition_ReadOnlyFile1()
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_Disposition_ReadOnlyFile1, 읽기 전용파일에 SetFileInformationByHandle을 호출");

    std::wstring fileName = GetTestFileName();
    BOOL fOk;

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastError() << endl;
        return;
    }

    File f1(fileName,
        GENERIC_READ | GENERIC_WRITE | DELETE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

    if(SetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_READONLY))
    {
        log.GetStream(TestLog::MT_ERROR) << L"읽기 전용 파일로 변경" << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"SetFileAttributes function failed." << GetLastError() << endl;
    }

    FILE_DISPOSITION_INFO dispositionInfo;

    dispositionInfo.DeleteFile = TRUE;

    fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

    if(fOk)
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"파일이 삭제 상태로 마킹됨." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"apiSetFileInformationByHandle가 실패했습니다." << endl;
        DeleteFileOrCheck(log, fileName);
        return;
    }

    if(DeleteFileOrCheck(log, fileName))
    {
        log.Ok();
    }
}

static void Test_SetFileInformationByHandle_Disposition_ReadOnlyFile2()
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_Disposition_ReadOnlyFile2, SetFileInformationByHandle로 Delete하고 핸들을 닫기 전에, 다른 곳에서 읽기 전용파일로 변경");

    std::wstring fileName = GetTestFileName();
    BOOL fOk;

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastError() << endl;
        return;
    }

    File f1(fileName,
        GENERIC_READ | GENERIC_WRITE | DELETE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

    FILE_DISPOSITION_INFO dispositionInfo;

    dispositionInfo.DeleteFile = TRUE;

    fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

    if(fOk)
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"파일이 삭제 상태로 마킹됨." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"apiSetFileInformationByHandle가 실패했습니다." << endl;
        DeleteFileOrCheck(log, fileName);
        return;
    }

    if(SetFileAttributes(fileName.c_str(), FILE_ATTRIBUTE_READONLY))
    {
        log.GetStream(TestLog::MT_ERROR) << L"읽기 전용 파일로 변경" << endl;
        log.GetStream(TestLog::MT_ERROR) << L"The function must be failed." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"SetFileAttributes function failed." << GetLastError() << endl;
    }

    if(DeleteFileOrCheck(log, fileName))
    {
        log.Ok();
    }
}

void Test_SetFileInformationByHandle_Delete_Twice()
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_Delete_Twice, ");

    std::wstring fileName = GetTestFileName(L"Test_SetFileInformationByHandle_Delete_Twice");
    
    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastErrorStr() << endl;
        return;
    }

    File f1(fileName,
        GENERIC_READ | GENERIC_WRITE | DELETE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

    FILE_DISPOSITION_INFO dispositionInfo;

    dispositionInfo.DeleteFile = TRUE;

    BOOL fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

    if(fOk)
    {
        log.GetStream(TestLog::MT_ERROR) <<
            L"파일이 삭제 상태로 마킹됨." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) <<
            L"apiSetFileInformationByHandle가 실패했습니다." << GetLastErrorStr() << std::endl;
    }

    // 파일을 열어본다.(파일이 삭제되어 있어야 함)
    {
        HANDLE h = apiCreateFile(fileName.c_str(),
            GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if(h != INVALID_HANDLE_VALUE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"SetFileInformation 오작동." << endl;
            CloseHandle(h);
        }
    }

    // 한번 더 삭제.
    fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

    if(fOk)
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"파일이 삭제 상태로 마킹됨." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"apiSetFileInformationByHandle가 실패했습니다." << GetLastErrorStr() << std::endl;
    }

    f1.CloseHandle();

    fOk = DeleteFile(fileName.c_str());
    if(fOk)
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"Delete File Succeed" << std::endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"DeleteFile Failed. " << GetLastErrorStr() << std::endl;
    }
    
    log.Ok();
}

static void Test_SetFileInformationByHandle_Delete_No_Have_Delete_DesireAccess()
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_Delete_File_No_Have_Delete_DesireAccess, ");

    std::wstring fileName = GetTestFileName(L"Test_SetFileInformationByHandle_Delete_File_No_Have_Delete_DesireAccess");

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastErrorStr() << endl;
        return;
    }

    File f1(fileName,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

    FILE_DISPOSITION_INFO dispositionInfo;

    dispositionInfo.DeleteFile = TRUE;

    BOOL fOk = apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo));

    if(fOk)
    {
        log.GetStream(TestLog::MT_ERROR) <<
            L"파일이 삭제 상태로 마킹됨." << endl;
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) <<
            L"apiSetFileInformationByHandle가 실패했습니다->" << GetLastError() << std::endl;
    }

    {
        HANDLE h = apiCreateFile(fileName.c_str(),
            GENERIC_READ, FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        if(h != INVALID_HANDLE_VALUE)
        {
            log.GetStream(TestLog::MT_MESSAGE) << L"The file's been opened." << endl;
            CloseHandle(h);
        }
    }

    f1.CloseHandle();

    fOk = DeleteFile(fileName.c_str());
    if(fOk)
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"Delete File Succeed" << std::endl;
    }
    else
    {
        log.GetStream(TestLog::MT_MESSAGE) <<
            L"DeleteFile Failed. " << GetLastError() << std::endl;
    }

    log.Ok();
}

void Test_SetFileInformationByHandle_FileTime(LARGE_INTEGER CreationTime,
                                                     LARGE_INTEGER LastAccessTime,
                                                     LARGE_INTEGER LastWriteTime,
                                                     LARGE_INTEGER ChangeTime)
{
    DEF_TESTLOG_T("Test_SetFileInformationByHandle_FileTime 테스트");

    std::wstring fileName = GetTestFileName();
    BOOL fOk;
    BOOL failed = FALSE;

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastErrorStr() << endl;
        failed = TRUE;
    }

    while(failed == FALSE)
    {
        File f1(fileName,
            GENERIC_READ | GENERIC_WRITE | DELETE,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

        FILE_BASIC_INFO basicInfo;

        basicInfo.CreationTime = CreationTime;
        basicInfo.LastAccessTime = LastAccessTime;
        basicInfo.LastWriteTime = LastWriteTime;
        basicInfo.ChangeTime = ChangeTime;
        basicInfo.FileAttributes = 0;

        Sleep(200);

        fOk = apiSetFileInformationByHandle(f1, FileBasicInfo, &basicInfo, sizeof(basicInfo));

        if(fOk)
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"GOOD." << endl;

            FILE_BASIC_INFO fbi;
            apiGetFileInformationByHandleEx(f1, FileBasicInfo, &fbi, sizeof(FILE_BASIC_INFO));
        }
        else
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"Failed" << endl;
            failed = TRUE;
            break;
        }

        break;
    }

    DeleteFileOrCheck(log, fileName);

    if(failed == FALSE)
    {
        log.Ok();
    }
}

void Test_Writefile_FileTime()
{
    DEF_TESTLOG_T("Test_Writefile_FileTime 테스트");

    std::wstring fileName = GetTestFileName();
    BOOL failed = FALSE;

    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << GetLastErrorStr() << endl;
        failed = TRUE;
    }

    Sleep(10000);

    

    while(failed == FALSE)
    {
        File f1(fileName,
            GENERIC_READ | GENERIC_WRITE | DELETE,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

        CHAR buf[100] = { 'A', };
        DWORD dwWrittenBytes;

        FILE_BASIC_INFO fbi;

        apiGetFileInformationByHandleEx(f1, FileBasicInfo, &fbi, sizeof(FILE_BASIC_INFO));

        if(WriteFile(f1, buf, 100, &dwWrittenBytes, 0))
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"GOOD." << dwWrittenBytes << endl;

            
            apiGetFileInformationByHandleEx(f1, FileBasicInfo, &fbi, sizeof(FILE_BASIC_INFO));
        }
        else
        {
            log.GetStream(TestLog::MT_MESSAGE) <<
                L"Failed" << endl;
            failed = TRUE;
            break;
        }

        Sleep(10000);
        {
            File f2(fileName,
                GENERIC_READ | GENERIC_WRITE | DELETE,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

            ZeroMemory(&fbi, sizeof(FILE_BASIC_INFO));
            apiGetFileInformationByHandleEx(f2, FileBasicInfo, &fbi, sizeof(FILE_BASIC_INFO));
        }
        Sleep(10000);

        f1.CloseHandle();

        {
        File f2(fileName,
            GENERIC_READ | GENERIC_WRITE | DELETE,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE);

        ZeroMemory(&fbi, sizeof(FILE_BASIC_INFO));
        apiGetFileInformationByHandleEx(f2, FileBasicInfo, &fbi, sizeof(FILE_BASIC_INFO));
        }

        break;
    }

    DeleteFileOrCheck(log, fileName);

    if(failed == FALSE)
    {
        log.Ok();
    }
}

BOOL RenameFile(HANDLE hFile, HANDLE hRootDirectory, LPCWSTR pRenamePath, BOOLEAN ReplaceIfExists)
{
    PFILE_RENAME_INFO pRename = (PFILE_RENAME_INFO)malloc(FIELD_OFFSET(FILE_RENAME_INFO, FileName[0]) + MAX_PATH * sizeof(WCHAR));

    if(pRename == 0)
    {
        return FALSE;
    }

    pRename->ReplaceIfExists = ReplaceIfExists;
    pRename->RootDirectory = hRootDirectory;
    pRename->FileNameLength = wcslen(pRenamePath) * sizeof(WCHAR);
    wcscpy_s(pRename->FileName, MAX_PATH, pRenamePath);

    BOOL result = apiSetFileInformationByHandle(hFile, FileRenameInfo, pRename,
        FIELD_OFFSET(FILE_RENAME_INFO, FileName[0]) + pRename->FileNameLength);

    if(result == 0)
    {
        _tprintf (_T("SetFileInformationByHandle Fail. LastError = %d.\n"),
            GetLastError());
    }

    free(pRename);

    return result;
}

void Test_DeleteFile_RenamedFile()
{
    DEF_TESTLOG_T("Test_DeleteFile_RenamedFile, 다른 핸들로 이름을 변경해버린 파일을 삭제");
    wstring fileName = GetTestFileName();

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    {
        File f1(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE | DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, OPEN_EXISTING);

        if(!f1.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
                GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L")" << endl;
            if(!DeleteFileOrCheck(log, fileName.c_str()))
            {
                log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
            }
            return;
        }

        File f2(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE | DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, OPEN_EXISTING);

        WCHAR psz[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, psz);

        wstring sNewName = (psz + (L"\\" + fileName)) + L"_Renamed";
        
        if(!RenameFile(f2, NULL, sNewName.c_str(), TRUE))
        {
            log.GetStream(TestLog::MT_ERROR) <<
                L"apiSetFileInformationByHandle가 실패했습니다." << GetLastErrorStr() << std::endl;
            return;
        }

        f2.CloseHandle();

        FILE_DISPOSITION_INFO dispositionInfo;
        dispositionInfo.DeleteFile = TRUE;

        if(apiSetFileInformationByHandle(f1, FileDispositionInfo, &dispositionInfo, sizeof(dispositionInfo)))
        {
            log.GetStream(TestLog::MT_ERROR) <<
                L"파일이 삭제 상태로 마킹됨." << endl;
        }
        else
        {
            log.GetStream(TestLog::MT_ERROR) <<
                L"apiSetFileInformationByHandle가 실패했습니다." << GetLastErrorStr() << std::endl;
        }
    }

    DeleteFile(fileName.c_str());

    log.Ok();
}
