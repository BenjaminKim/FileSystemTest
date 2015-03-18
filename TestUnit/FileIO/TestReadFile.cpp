#include "stdafx.h"
#include "TestReadFile.h"
#include "FileIO/ApiReadFile.h"
#include "FileIO/ApiWriteFile.h"
#include "../File.h"

using namespace std;

void Test_ReadFileAll()
{
}

#define LODWORD(l)           ((DWORD)(((UINT64)(l)) & 0xffffffff))
#define HIDWORD(l)           ((DWORD)((((UINT64)(l)) >> 32) & 0xffffffff))

void Test_ReadFileOverlapped()
{
    DEF_TESTLOG_T("Test_ReadFileOverlapped, Basic file async I/O");

    HANDLE hFile = CreateFile(L"D:\\ReadFileTest1", GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_FLAG_OVERLAPPED /*| FILE_FLAG_NO_BUFFERING*/, 0);

    const int bufsize = 100*1024*1024;
    CHAR* readbuffer = new CHAR[bufsize+ 2];

    INT64 jTotalReadBytes = 0;
    for(;;)
    {
        OVERLAPPED gOverLapped;
        gOverLapped.Offset     = LODWORD(jTotalReadBytes);
        gOverLapped.OffsetHigh = HIDWORD(jTotalReadBytes); 
        gOverLapped.hEvent     = 0;

        DWORD nBytesRead = 0;
        
        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"ReadFile before." << endl;
        BOOL bResult = ReadFile(hFile, readbuffer, bufsize, 0, &gOverLapped);
        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"ReadFile returned." << endl;
        
        //log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"read bytes : " << nBytesRead << endl;
        //size_t len = strlen(readbuffer);
        //log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"readbuffer len : " << len << endl;

        DWORD dwError;
        if (!bResult) 
        { 
            // deal with the error code 
            switch (dwError = GetLastError()) 
            { 
            case ERROR_HANDLE_EOF: 
                { 
                    // we have reached the end of the file 
                    // during the call to ReadFile 

                    goto END;
                } 

            case ERROR_IO_PENDING: 
            case 996:
                { 
                    // asynchronous i/o is still in progress 

                    // do something else for a while 
                        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"before wait " << endl;
                        WaitForSingleObject( hFile, INFINITE );
                        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"WaitForSingleObject returned " << endl;

                        // check on the results of the asynchronous read 
                        bResult = GetOverlappedResult(hFile, &gOverLapped, 
                            &nBytesRead, FALSE) ; 

                        jTotalReadBytes += nBytesRead;
                        size_t len = strlen(readbuffer);
                        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"readbuffer len : " << len << endl;

                        // if there was a problem ... 
                        if (!bResult) 
                        { 
                            // deal with the error code 
                            switch (dwError = GetLastError()) 
                            { 
                            case ERROR_HANDLE_EOF: 
                                { 
                                    // we have reached the end of
                                    // the file during asynchronous
                                    // operation
                                    goto END;
                                } 

                                // deal with other error cases 
                            }   //end switch (dwError = GetLastError()) 
                        }

                } // end case 

                // deal with other error cases, such as the default 

            } // end switch (dwError = GetLastError()) 
        } // end if     
    } //end of while

END:
    delete[] readbuffer;

    log.Ok();
}

void Test_WriteFileOverlapped()
{
    DEF_TESTLOG_T("Test_WriteFileOverlapped, Basic Async Writing Test");

    HANDLE hFile = CreateFile(L"D:\\WriteFileTest", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED /*| FILE_FLAG_NO_BUFFERING*/, 0);

    const int bufsize = 64*1024/**1024*/;
    CHAR* writebuffer = new CHAR[bufsize+ 1];
    memset(writebuffer, 65, bufsize);
    memset(writebuffer + bufsize, 0, 1);

    INT64 jTotalReadBytes = 0;
    for(;;)
    {
        OVERLAPPED gOverLapped;
        gOverLapped.Offset     = LODWORD(jTotalReadBytes);
        gOverLapped.OffsetHigh = HIDWORD(jTotalReadBytes); 
        gOverLapped.hEvent     = 0;

        DWORD nBytesRead = 0;

        if(gOverLapped.OffsetHigh > 0)
        {
            goto END;
        }
        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"ReadFile before." << endl;
        BOOL bResult = WriteFile(hFile, writebuffer, bufsize, 0, &gOverLapped);
        log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"ReadFile returned." << endl;

        //log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"read bytes : " << nBytesRead << endl;
        //size_t len = strlen(readbuffer);
        //log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"readbuffer len : " << len << endl;

        DWORD dwError;
        if (!bResult) 
        { 
            // deal with the error code 
            switch (dwError = GetLastError()) 
            { 
            case ERROR_HANDLE_EOF: 
                { 
                    // we have reached the end of the file 
                    // during the call to ReadFile 

                    goto END;
                } 

            case ERROR_IO_PENDING: 
                { 
                    // asynchronous i/o is still in progress 

                    // do something else for a while 
                    log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"before wait " << endl;
                    WaitForSingleObject( hFile, INFINITE );
                    log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"waitfor singleobject returned " << endl;

                    // check on the results of the asynchronous read 
                    bResult = GetOverlappedResult(hFile, &gOverLapped, 
                        &nBytesRead, FALSE) ; 

                    jTotalReadBytes += nBytesRead;
                    size_t len = strlen(writebuffer);
                    log.GetStream(TestLog::MT_MESSAGE) << Timer::GetCurrentDateTime() << L"readbuffer len : " << len << endl;

                    // if there was a problem ... 
                    if (!bResult) 
                    { 
                        // deal with the error code 
                        switch (dwError = GetLastError()) 
                        { 
                        case ERROR_HANDLE_EOF: 
                            { 
                                // we have reached the end of
                                // the file during asynchronous
                                // operation
                                goto END;
                            } 

                            // deal with other error cases 
                        }   //end switch (dwError = GetLastError()) 
                    }

                } // end case 

                // deal with other error cases, such as the default 

            } // end switch (dwError = GetLastError()) 
        } // end if     
    } //end of while

END:
    delete[] writebuffer;

    log.Ok();
}

void Test_ReadWriteFileNormal()
{
    DEF_TESTLOG_T("ReadWriteFileNormal");

    wstring fileName(L"ReadWriteFileNormal.txt");
    if(!TouchFile(log, fileName))
    {
        log.GetStream(TestLog::MT_ERROR) << L"Failed to create a file." << endl;
        return;
    }

    File f(fileName, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, CREATE_ALWAYS);
   
    TCHAR buffer[] = L"Test1234567890 Test1234567890 Test1234567890 Test1234567890 Test1234567890\r\n";
    DWORD writeBytes = 0;
    BOOL fOk = apiWriteFile(f, buffer, sizeof(buffer), &writeBytes, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile" << endl;
        return;
    }
    if(writeBytes != sizeof(buffer))
    {
        log.GetStream(TestLog::MT_ERROR) << L"WriteFile: writeBytes Error." << endl;
        return;
    }

    TCHAR readbuffer[256];
    DWORD bytesRead = 0;
    fOk = apiReadFile((HANDLE)f, readbuffer, sizeof(readbuffer), &bytesRead, 0);

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"ReadFile" << endl;
        return;
    }
    if(bytesRead != sizeof(buffer))
    {
        log.GetStream(TestLog::MT_ERROR) << L"ReadFile: readBytes Error." << GetLastErrorStr() << endl;
        log.GetStream(TestLog::MT_ERROR) << L"ReadString: " << readbuffer << endl;
        return;
    }

    log.Ok();
}


void ReadWriteTest()
{
    /*DEF_TESTLOG_T("ReadWriteTest");

    std::wstring fileName = GetTestFileName(L"ReadWriteTest");

    bool fOk = MakeFile(log, fileName.c_str());

    if(!fOk)
    {
        log.GetStream(TestLog::MT_ERROR) << L"Cannot create a file." << endl;
        return;
    }

    File f(fileName, FILE_GENERIC_READ | FILE_GENERIC_WRITE, FILE_SHARE_DELETE, OPEN_EXISTING);

    CHAR buf[17] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', '\0' };
    CHAR buf2[20] = { 0, };
    DWORD cbWritten;
    WriteFile(f, buf, sizeof(buf), &cbWritten, 0);
    SetFilePointerEx(f, 10, NULL, FILE_BEGIN);
    SetEndOfFile(f);
    DWORD cbRead;
    ReadFile(f, buf2, 17, &cbRead, 0);

    std::string s1 = buf;
    std::string s2 = buf2;

    if(s1 == s2)
    {
    }
    else
    {
    }*/
}