#include "stdafx.h"
#include "FileManagement/ApiDeleteFile.h"
#include "TestUnit/FileManagement/TestFindFirstFile.h"
#include "File.h"
#include "FileManagement/ApiFindFirstFile.h"
#include "FileManagement/ApiFindNextFile.h"
#include "FileManagement/ApiFindClose.h"
#include "DirectoryManagement/ApiRemoveDirectory.h"
#include "FileIO/ApiWriteFile.h"
#include "FileIo/ApiReadFile.h"

using namespace std;

void PrintStatistics(const wstring& functionName, ApiStatistics* pStatistics)
{
    if(pStatistics->Count())
    {
        wcout.precision(12);
        wcout << L"Function Name : " << functionName << endl;
        wcout << L"Min : " << fixed << pStatistics->Min() << endl;
        wcout << L"Max : " << fixed << pStatistics->Max() << endl;
        wcout << L"Sum : " << fixed << pStatistics->Sum() << endl;
        wcout << L"Count : " << fixed << pStatistics->Count() << endl;
        wcout << L"Operation per sec : " << fixed << pStatistics->Count() / pStatistics->Sum() << endl;
        wcout << L"Avg : " << fixed << pStatistics->Avg() << endl;
        wcout << L"StdDev : " << fixed << pStatistics->StdDev() << endl << endl;
    }
}

void PrintStatistics(const wstring& functionName, INT64 SendBytes, ApiStatistics* pStatistics)
{
    if(pStatistics->Count() == 0)
    {
        return;
    }
    
    wcout.precision(12);
    wcout << L"Function Name : " << functionName << endl;
    wcout << L"Min : " << fixed << pStatistics->Min() << endl;
    wcout << L"Max : " << fixed << pStatistics->Max() << endl;
    wcout << L"Sum : " << fixed << pStatistics->Sum() << endl;
    wcout << L"Count : " << fixed << pStatistics->Count() << endl;
    wcout << L"Operation per sec : " << fixed << pStatistics->Count() / pStatistics->Sum() << endl;
    wcout << L"Avg : " << fixed << pStatistics->Avg() << endl;
    wcout << L"Send Bytes : " << fixed << SendBytes << endl;
    wcout << L"StdDev : " << fixed << pStatistics->StdDev() << endl << endl;
}

void CreateDeleteFile()
{
    DEF_TESTLOG_T("CreateDeleteFile, ");   

    wstring fileName = GetTestFileName(L"CreateDeleteFile");

    HANDLE h = apiCreateFile(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 0, CREATE_ALWAYS, 0, 0);
    if(h == INVALID_HANDLE_VALUE)
    {
        log.GetStream(TestLog::MT_ERROR) << L"CreaeteFile error." << std::endl;
        return;
    }

    BOOL fOk = apiDeleteFile(fileName.c_str());
    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"DeleteFile error." << std::endl;
        return;
    }

    log.Ok();
}

void CreateManyFiles_And_DeleteTheFiles(size_t iFileNum)
{
    WaitUntilStartTime();

    for(size_t i = 0; i < iFileNum; ++i)
    {
        CreateDeleteFile();
        if(IsTimeToEnd())
            break;
    }
}

void CreateManyFiles_And_DeleteTheFiles_Deep(size_t iFileNum)
{
    if(iFileNum > 15)
        iFileNum = 15;

    WaitUntilStartTime();
    if(IsTimeToEnd())
        return;

    DEF_TESTLOG_T("CreateManyFiles_And_DeleteTheFiles_Deep, ");

    vector<std::wstring> vCreateFiles;
    wstring dirname = GetTestFileName(L"dir");
    wstring basedir = GetWidTestBasePath();

    for(size_t i = 0; i < iFileNum; ++i)
    {
        basedir = basedir + L"\\" + dirname;
        TouchManyFiles(log, 5, basedir, vCreateFiles, false);
    }

    basedir = GetWidTestBasePath();

    size_t i = 0;
    for(;;)
    {
        if(i >= vCreateFiles.size())
        {
            break;
        }

        basedir = basedir + L"\\" + dirname;
        for(size_t j = 0; j < 5; ++j)
        {
            BOOL fOk = apiDeleteFile((basedir + L"\\" + vCreateFiles[i++]).c_str());
            if(!fOk)
            {
                log.GetStream(TestLog::MT_ERROR) << L"DeleteFile error." << std::endl;
                break;
            }
        }
    }

    while(uRemoveDirectory(basedir.c_str()))
    {
        basedir = basedir.substr(0, basedir.rfind(L"\\"));
    }

    log.Ok();
}

void ListFiles(TestLog& log, const wstring& dirpath)
{
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError;

    WIN32_FIND_DATA wfd;

    // Find the first file in the directory.
    hFind = apiFindFirstFile(dirpath.c_str(), &wfd);

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

void CreateSomeFiles_And_ListTheFiles(size_t fileNum, size_t loopCount, ApiStatistics* pStatistics)
{
    DEF_TESTLOG_T("CreateSomeFiles_And_ListTheFiles, ");

    wstring dirpath(GetTestFileName(L"filelisting"));

    // Create files
    vector<wstring> vCreateFiles;
    TouchManyFiles(log, fileNum, GetWidTestBasePath() + L"\\" + dirpath, vCreateFiles, false);

    WaitUntilStartTime();
    
    // List files
    for(size_t i = 0; i < loopCount; ++i)
    {
        Timer t;
        ListFiles(log, GetWidTestBasePath() + L"\\" + dirpath);
        double d = t.GetElapsedTime();

        if(pStatistics)
        {
            pStatistics->InsertData(d);
        }

        if(IsTimeToEnd())
            break;
    }

    // Delete files   
    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        BOOL fOk = uDeleteFile((GetWidTestBasePath() + L"\\" + dirpath + L"\\" + vCreateFiles[i]).c_str());
        if(!fOk)
        {
            log.GetStream(TestLog::MT_ERROR) << L"FindNextFile error. Error is " << GetLastErrorStr() << std::endl;
            break;
        }
    }

    uRemoveDirectory((GetWidTestBasePath() + L"\\" + dirpath).c_str());

    PrintStatistics(L"CreateSomeFiles_And_ListTheFiles", pStatistics);
    
    log.Ok();
}

void WriteFileTest_(size_t sizeKB, size_t buffersizeKB, ApiStatistics* pStatistics, INT64& jWrittenBytes)
{
    DEF_TESTLOG_T("WriteFileTest, ");
    std::wstring fileName = GetTestFileName(L"WriteFileTest");

    jWrittenBytes = 0;  

    BOOL fOk = FALSE;
    //////////////////////////////////////////////////////////////////////////
    {
        File f(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_READ, CREATE_ALWAYS);

        if(!f.IsValidHandle())
        {
            log.GetStream(TestLog::MT_ERROR) << L"CreateFile" << endl;
            fOk = FALSE;
            goto END;
        }

        if(buffersizeKB == 0)
        {
            buffersizeKB = 1;
        }

        char* buffer = new char[buffersizeKB * 1024];

        for(size_t i = 0; i < buffersizeKB; i++)
        {
            memcpy_s(buffer + (1024 * i), 1024, "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789"
                "ABCDEFGHIJKLMNOPQRSTUV\r\n", 1024 );
        }

        DWORD writeBytes = 0;

        for(size_t x = 0; x < sizeKB; x += buffersizeKB)
        {        
            Timer t;
            double d = t.GetElapsedTime();
            if(uWriteFile(f, buffer, buffersizeKB * 1024, &writeBytes, 0) == FALSE)
            {
                log.GetStream(TestLog::MT_ERROR) << L"WriteFile" << endl;
                delete[] buffer;
                fOk = FALSE;
                goto END;
            }

            d = t.GetElapsedTime();
            if(pStatistics)
            {
                pStatistics->InsertData(d);
            }

            jWrittenBytes += writeBytes;

            if(IsTimeToEnd())
            {
                delete[] buffer;
                fOk = TRUE;
                goto END;
            }

            if(writeBytes != buffersizeKB * 1024)
            {
                log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
                delete[] buffer;
                fOk = FALSE;
                goto END;
            }
        } // main loop end.

        delete[] buffer;

        log.GetStream(TestLog::MT_MESSAGE) << L"<" << fileName << L"> file created." << endl;
        fOk = TRUE;
    } // The file handle be closed automatically.

END:
    uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"颇老 积己 角菩" << endl;
        return;
    }

    log.Ok();
}

void WriteFileTest(size_t sizeKB, size_t bufferSize, ApiStatistics* pStatistics)
{
    WaitUntilStartTime();

    INT64 jWrittenBytes = 0;
    for(size_t i = 0; i < 5000000; ++i)
    {
        WriteFileTest_(sizeKB, bufferSize, pStatistics, jWrittenBytes);

        if(IsTimeToEnd())
            break;
    }

    PrintStatistics(L"WriteFileTest", jWrittenBytes, pStatistics);
}

void ReadFileTest_(size_t sizeKB, size_t buffersizeKB, ApiStatistics* pStatistics, INT64& jReadBytes)
{
    DEF_TESTLOG_T("ReadFileTest_, ");
    std::vector<wstring> v;
    for( size_t t = 1; t <= 50; ++t)
    {
        std::wostringstream oss;
        oss << t;
        v.push_back(oss.str());
    }

    std::wstring fileName = L"Z:\\ReadFileTest";

    jReadBytes = 0;

    BOOL fOk = FALSE;
    //////////////////////////////////////////////////////////////////////////
    for(size_t i = 0; ; ++i)
    {
        File f(fileName + v[i % v.size()], GENERIC_READ, 0, OPEN_EXISTING);

        if(!f.IsValidHandle())
        {
            continue;
            //log.GetStream(TestLog::MT_ERROR) << L"The File not exist." << endl;
            //fOk = FALSE;
            //goto END;
        }

        if(buffersizeKB == 0)
        {
            buffersizeKB = 1;
        }

        char* buffer = new char[buffersizeKB * 1024];

        DWORD readBytes = 0;

        for(size_t x = 0; x < sizeKB; x += buffersizeKB)
        {        
            Timer t;
            double d = t.GetElapsedTime();
            if(uReadFile(f, buffer, buffersizeKB * 1024, &readBytes, 0) == FALSE)
            {
                log.GetStream(TestLog::MT_ERROR) << L"ReadFile" << endl;
                delete[] buffer;
                fOk = FALSE;
                goto END;
            }

            d = t.GetElapsedTime();
            
            if(pStatistics)
            {
                pStatistics->InsertData(d);
            }

            if(buffersizeKB*1024 != readBytes)
            {
                log.GetStream(TestLog::MT_ERROR) << L"ReadFile Size Error" << endl;
                delete[] buffer;
                fOk = FALSE;
                goto END;
            }

            jReadBytes += readBytes;

            if(IsTimeToEnd())
            {
                delete[] buffer;
                fOk = TRUE;
                goto END;
            }

            if(readBytes != buffersizeKB * 1024)
            {
                log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
                delete[] buffer;
                fOk = FALSE;
                goto END;
            }
        } // main loop end.

        delete[] buffer;

        log.GetStream(TestLog::MT_MESSAGE) << L"<" << fileName << L"> file created." << endl;
        fOk = TRUE;
        break;
    } // The file handle be closed automatically.

END:
//    uDeleteFile(fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"颇老 积己 角菩" << endl;
        return;
    }

    log.Ok();
}

void ReadFileTest(size_t sizeKB, size_t bufferSize, ApiStatistics* pStatistics)
{
    WaitUntilStartTime();

    INT64 jReadBytes = 0;
    for(size_t i = 0; i < 50; ++i)
    {
        ReadFileTest_(sizeKB, bufferSize, pStatistics, jReadBytes);

        if(IsTimeToEnd())
            break;
    }

    PrintStatistics(L"WriteFileTest", jReadBytes, pStatistics);
}

void OpenCloseFile(const vector<std::wstring>& v)
{
    DEF_TESTLOG_T("OpenCloseFile, ");

    for(size_t i = 0; i < v.size(); ++i)
    {
        File f(v[i]);
        f.CloseHandle();
    }

    log.Ok();
}

void OpenCloseFileTest(size_t fileNum, size_t loopCount)
{
    vector<std::wstring> vCreateFiles;
    {
        DEF_TESTLOG_T("OpenCloseFileTest, ");
        TouchManyFiles(log, fileNum, GetWidTestBasePath(), vCreateFiles, false);
        log.Ok();
    }
    uCreateFile.ResetStatistics();

    WaitUntilStartTime();
    for(size_t i = 0; i < loopCount; ++i)
    {
        OpenCloseFile(vCreateFiles);
        if(IsTimeToEnd())
        {
            break;
        }
    }

    for(size_t i = 0; i < vCreateFiles.size(); ++i)
    {
        apiDeleteFile((GetWidTestBasePath() + L"\\" + vCreateFiles[i]).c_str());
    }
}