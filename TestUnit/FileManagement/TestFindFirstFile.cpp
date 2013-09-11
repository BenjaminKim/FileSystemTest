#include "stdafx.h"
#include "TestFindFirstFile.h"
#include "FileManagement/ApiFindFirstFile.h"
#include "FileManagement/ApiFindNextFile.h"
#include "../File.h"
#include "FileManagement/ApiFindClose.h"
#include "FileManagement/ApiDeleteFile.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"

using namespace std;

void Test_FindFirstFile_ManyFiles_With_Wildcard(size_t fileNum)
{
    DEF_TESTLOG_T("Test_FindFirstFile_ManyFiles_With_Wildcard, 많은 파일을 생성 후 와일드 카드를 사용해서 탐색테스트");

    vector<wstring> vCreateFiles;
    wstring dirname = L"\\" + GetTestFileName() + L"ManyFiles";
    TouchManyFiles(log, fileNum, GetWidTestBasePath() + dirname, vCreateFiles, false);

    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError;

    WIN32_FIND_DATA wfd;

    // Find the first file in the directory.
    hFind = apiFindFirstFile((GetWidTestBasePath() + dirname + L"\\*").c_str(), &wfd);

    if(hFind == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
        return;
    }
    else 
    {
        log.GetStream(TestLog::MT_ERROR) << L"First file name is " << wfd.cFileName << std::endl;

        // List all the other files in the directory.

        for(;;)
        {
            if(apiFindNextFile(hFind, &wfd) == 0)
            {
                break;
            }

            log.GetStream(TestLog::MT_ERROR) << L"Next file name is " << wfd.cFileName << std::endl;
        }

        dwError = GetLastError();
        uFindClose(hFind);
        if(dwError != ERROR_NO_MORE_FILES)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
        }
    }   

    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        BOOL fOk = uDeleteFile((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            break;
        }
    }

    uRemoveDirectory((GetWidTestBasePath() + dirname).c_str());

    log.Ok();
}

void Test_FindFirstFile_ManyFiles_With_NoWildcard(size_t fileNum)
{
    DEF_TESTLOG_T("Test_FindFirstFile_ManyFiles_With_NoWildcard, 매우 많은 파일을 생성 후 탐색 테스트. 와일드 카드 없이 하나씩 찾아본다.");

    vector<wstring> vCreateFiles;
    wstring dirname = L"\\" + GetTestFileName() + L"ManyFiles";
    TouchManyFiles(log, fileNum, GetWidTestBasePath() + dirname, vCreateFiles, false);

    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError;

    WIN32_FIND_DATA wfd;
    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        LPCTSTR DirSpec = 0;
        DirSpec = (GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str();

        // Find the first file in the directory.
        hFind = apiFindFirstFile((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str(), &wfd);

        if(hFind == INVALID_HANDLE_VALUE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
            break;
        }
        else 
        {
            log.GetStream(TestLog::MT_ERROR) << L"First file name is " << wfd.cFileName << std::endl;

            // List all the other files in the directory.

            for(;;)
            {
                if(apiFindNextFile(hFind, &wfd) == 0)
                {
                    dwError = GetLastError();
                    break;
                }

                log.GetStream(TestLog::MT_ERROR) << L"Next file name is " << wfd.cFileName << std::endl;
            }
            
            uFindClose(hFind);
            if(dwError != ERROR_NO_MORE_FILES)
            {
                log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            }
        }
        
        BOOL fOk = uDeleteFile((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            break;
        }
    } // end loop

    uRemoveDirectory((GetWidTestBasePath() + dirname).c_str());

    log.Ok();
}

void Test_FindFirstFile_Directory_With_Wildcard(size_t dirNum)
{
    DEF_TESTLOG_T("Test_FindFirstFile_FindALotOfFiles, 많은 파일을 생성 후 와일드 카드를 사용해서 탐색테스트");

    vector<wstring> vCreateFiles;
    wstring dirname = L"\\" + GetTestFileName() + L"ManyFiles";
    TouchManyFiles(log, dirNum, GetWidTestBasePath() + dirname, vCreateFiles, true);

    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError;

    WIN32_FIND_DATA wfd;

    // Find the first file in the directory.
    hFind = apiFindFirstFile((GetWidTestBasePath() + dirname + L"\\*").c_str(), &wfd);

    if(hFind == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
        return;
    }
    else 
    {
        log.GetStream(TestLog::MT_ERROR) << L"First file name is " << wfd.cFileName << std::endl;

        // List all the other files in the directory.

        for(;;)
        {
            if(apiFindNextFile(hFind, &wfd) == 0)
            {
                break;
            }

            log.GetStream(TestLog::MT_ERROR) << L"Next file name is " << wfd.cFileName << std::endl;
        }

        dwError = GetLastError();
        uFindClose(hFind);
        if(dwError != ERROR_NO_MORE_FILES)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
        }
    }   

    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        BOOL fOk = uRemoveDirectory((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
        }
    }

    uRemoveDirectory((GetWidTestBasePath() + dirname).c_str());

    log.Ok();
}

void Test_FindFirstFile_Directory_With_NoWildcard(size_t dirNum)
{
    DEF_TESTLOG_T("Test_FindFirstFile_Directory_With_NoWildcard, 매우 많은 파일을 생성 후 탐색 테스트. 와일드 카드 없이 하나씩 찾아본다.");

    vector<wstring> vCreateFiles;
    wstring dirname = L"\\" + GetTestFileName() + L"ManyFiles";
    TouchManyFiles(log, dirNum, GetWidTestBasePath() + dirname, vCreateFiles, true);

    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError;

    WIN32_FIND_DATA wfd;
    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        LPCTSTR DirSpec = 0;
        DirSpec = (GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str();

        // Find the first file in the directory.
        hFind = apiFindFirstFile((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str(), &wfd);

        if(hFind == INVALID_HANDLE_VALUE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
            break;
        }
        else 
        {
            log.GetStream(TestLog::MT_ERROR) << L"First file name is " << wfd.cFileName << std::endl;

            // List all the other files in the directory.

            for(;;)
            {
                if(apiFindNextFile(hFind, &wfd) == 0)
                {
                    dwError = GetLastError();
                    break;
                }

                log.GetStream(TestLog::MT_ERROR) << L"Next file name is " << wfd.cFileName << std::endl;
            }

            uFindClose(hFind);
            if(dwError != ERROR_NO_MORE_FILES)
            {
                log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            }
        }

        BOOL fOk = uRemoveDirectory((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
        }
    } // end loop

    uRemoveDirectory((GetWidTestBasePath() + dirname).c_str());

    log.Ok();
}

void Test_FindFirstFile_DeletePending()
{
    DEF_TESTLOG_T("Test_FindFirstFile_DeletePending, Delete pending된 상태의 파일이 어떻게 보여지는지 테스트");

    std::wstring fileName = GetTestFileName(L"Test_FindFirstFile_DeletePending");
    
    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }
   
    File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);

    if(!f.IsValidHandle())
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreateFile, LastError = " <<
            GetLastError() << L"(" << GetErrorDefineString(GetLastError()) << L")" << endl;
        if(!DeleteFileOrCheck(log, fileName.c_str()))
        {
            log.GetStream(TestLog::MT_ERROR) << L"Cannot delete the file created before." << endl;
        }
        return;
    }

    uDeleteFile(fileName.c_str());
    //// delete pending

    HANDLE hFind = INVALID_HANDLE_VALUE;
//   DWORD dwError;

    WIN32_FIND_DATA wfd;

    // Find the first file in the directory.
    hFind = apiFindFirstFile(fileName.c_str(), &wfd);

    if(hFind == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
        return;
    }
    else 
    {
        log.GetStream(TestLog::MT_MESSAGE) << L"First file name is " << wfd.cFileName << std::endl;

        // List all the other files in the directory.

        for(;;)
        {
            if(apiFindNextFile(hFind, &wfd) == 0)
            {
                break;
            }

            log.GetStream(TestLog::MT_MESSAGE) << L"Next file name is " << wfd.cFileName << std::endl;
        }

        uFindClose(hFind);
    }
    
    f.CloseHandle();

    log.Ok();
}

void Test_FindFirstFile_CreateManyFiles_And_Listring_With_Wildcard(size_t fileNum, size_t listCount)
{
    DEF_TESTLOG_T("Test_FindFirstFile_CreateManyFiles_And_Listring_With_Wildcard, 많은 파일을 생성 후 와일드 카드를 사용해서 탐색테스트");

    vector<wstring> vCreateFiles;
    wstring dirname = L"\\" + GetTestFileName() + L"ManyFiles";
    TouchManyFiles(log, fileNum, GetWidTestBasePath() + dirname, vCreateFiles, false);

    size_t i = 0;
    while(i++ < listCount)
    {
        HANDLE hFind = INVALID_HANDLE_VALUE;
        DWORD dwError;

        WIN32_FIND_DATA wfd;

        vector<wstring> v;
        TouchManyFiles(log, 1, GetWidTestBasePath() + dirname, v, false);

        if(v.size() > 0)
        {
            DeleteFile(v[0].c_str());
        }

        // Find the first file in the directory.
        hFind = apiFindFirstFile((GetWidTestBasePath() + dirname + L"\\*").c_str(), &wfd);

        if(hFind == INVALID_HANDLE_VALUE)
        {
            log.GetStream(TestLog::MT_ERROR) << L"Invalid file handle. Error is " << GetLastErrorStr() << std::endl;
            return;
        }
        else 
        {
            log.GetStream(TestLog::MT_ERROR) << L"First file name is " << wfd.cFileName << std::endl;

            // List all the other files in the directory.

            for(;;)
            {
                if(apiFindNextFile(hFind, &wfd) == 0)
                {
                    break;
                }

                log.GetStream(TestLog::MT_ERROR) << L"Next file name is " << wfd.cFileName << std::endl;
            }

            dwError = GetLastError();
            uFindClose(hFind);
            if(dwError != ERROR_NO_MORE_FILES)
            {
                log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            }
        }   
    }

    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        BOOL fOk = uDeleteFile((GetWidTestBasePath() + dirname + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"uDeleteFile error." << endl;
            break;
        }
    }

    uRemoveDirectory((GetWidTestBasePath() + dirname).c_str());

    log.Ok();
}
