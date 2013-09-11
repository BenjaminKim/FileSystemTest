// WidTestUnit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestUnit/AllTest.h"
#include "TestUnit/TestLog.h"
#include "TestUnit/PTest.h"
#include "AllApi.h"

#pragma warning( push )
#pragma warning( disable : 4512 )
#include <boost/program_options.hpp>
#pragma warning( pop )

using namespace boost;
using namespace boost::program_options;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL SetBasePath(const std::wstring& s)
{
    if(::SetCurrentDirectoryW(s.c_str()))
    {
        wcout << L"Current directory path has been set as " << s << std::endl;
        return TRUE;
    }
    else
    {
        wcout << L"Failed to set current directory" << std::endl;
        return FALSE;
    }
}

void GetFunctions(__out std::vector<ApiFunction *>& vFunction)
{
    std::wcout << GetString_dwFileAttributes(8224) << std::endl;
    vFunction.clear();

    vFunction.push_back(&apiCreateDirectory);
    vFunction.push_back(&apiCreateDirectoryEx);
    vFunction.push_back(&apiCreateDirectoryTransacted);
    vFunction.push_back(&apiFindCloseChangeNotification);
    vFunction.push_back(&apiFindFirstChangeNotification);
    vFunction.push_back(&apiFindNextChangeNotification);
    vFunction.push_back(&apiGetCurrentDirectory);
    vFunction.push_back(&apiReadDirectoryChangesW);
    vFunction.push_back(&apiRemoveDirectory);
    vFunction.push_back(&apiRemoveDirectoryTransacted);
    vFunction.push_back(&apiSetCurrentDirectory);

    vFunction.push_back(&apiCancelIo);
    vFunction.push_back(&apiCancelIoEx);
    vFunction.push_back(&apiCancelSynchronousIo);
    vFunction.push_back(&apiCreateIoCompletionPort);
    vFunction.push_back(&apiFlushFileBuffers);
    vFunction.push_back(&apiGetQueuedCompletionStatus);
    vFunction.push_back(&apiGetQueuedCompletionStatusEx);
    vFunction.push_back(&apiLockFile);
    vFunction.push_back(&apiLockFileEx);
    vFunction.push_back(&apiPostQueuedCompletionStatus);
    vFunction.push_back(&apiReadFile);
    vFunction.push_back(&apiWriteFile);
    vFunction.push_back(&apiReadFileEx);
    vFunction.push_back(&apiReadFileScatter);
    vFunction.push_back(&apiSetEndOfFile);
    vFunction.push_back(&apiSetFilePointerEx);
    vFunction.push_back(&apiSetFileCompletionNotificationModes);
    vFunction.push_back(&apiSetFileIoOverlappedRange);
    vFunction.push_back(&apiSetFilePointer);
    vFunction.push_back(&apiUnlockFile);
    vFunction.push_back(&apiUnlockFileEx);
    vFunction.push_back(&apiWriteFileEx);
    vFunction.push_back(&apiWriteFileGather);

    vFunction.push_back(&apiCopyFile);
    vFunction.push_back(&apiCopyFileEx);
    vFunction.push_back(&apiCreateFile);
    vFunction.push_back(&apiDeleteFile);
    vFunction.push_back(&apiFindFirstFile);
    vFunction.push_back(&apiFindNextFile);
    vFunction.push_back(&apiFindFirstFileEx);
    vFunction.push_back(&apiFindFirstFileNameW);
    vFunction.push_back(&apiFindFirstStreamW);
    vFunction.push_back(&apiFindNextStreamW);
    vFunction.push_back(&apiGetBinaryType);
    vFunction.push_back(&apiGetCompressedFileSize);
    vFunction.push_back(&apiGetFileAttributes);
    vFunction.push_back(&apiGetFileAttributesEx);
    vFunction.push_back(&apiGetFileInformationByHandle);
    vFunction.push_back(&apiGetFileInformationByHandleEx);
    vFunction.push_back(&apiGetFileSize);
    vFunction.push_back(&apiGetFileSizeEx);
    vFunction.push_back(&apiGetFileType);
    vFunction.push_back(&apiGetFinalPathNameByHandle);
    vFunction.push_back(&apiSetFileAttributes);
    vFunction.push_back(&apiSetFileTime);
    vFunction.push_back(&apiSetFileTime);
    vFunction.push_back(&apiGetFullPathName);
    vFunction.push_back(&apiGetLongPathName);
    vFunction.push_back(&apiGetShortPathName);
    vFunction.push_back(&apiGetTempFileName);
    vFunction.push_back(&apiGetTempPath);
    vFunction.push_back(&apiMoveFile);
    vFunction.push_back(&apiMoveFileEx);
    vFunction.push_back(&apiMoveFileWithProgress);
    vFunction.push_back(&apiReplaceFile);
    vFunction.push_back(&apiSearchPath);
    vFunction.push_back(&apiSetFileInformationByHandle);
    vFunction.push_back(&apiSetFileValidData);

    vFunction.push_back(&apiGetDiskFreeSpace);
    vFunction.push_back(&apiGetDiskFreeSpaceEx);

    vFunction.push_back(&apiFindFirstVolume);
    vFunction.push_back(&apiFindNextVolume);
    vFunction.push_back(&apiFindVolumeClose);
    vFunction.push_back(&apiQueryDosDevice);
    vFunction.push_back(&apiGetVolumePathNamesForVolumeName);
    vFunction.push_back(&apiGetVolumeNameForVolumeMountPoint);
    vFunction.push_back(&apiFindFirstVolumeMountPoint);
    vFunction.push_back(&apiFindNextVolumeMountPoint);
    vFunction.push_back(&apiFindVolumeMountPointClose);
    vFunction.push_back(&apiGetDriveType);
    vFunction.push_back(&apiGetLogicalDrives);
    vFunction.push_back(&apiGetLogicalDriveStrings);
    vFunction.push_back(&apiGetVolumeInformation);
    vFunction.push_back(&apiGetVolumeInformationByHandleW);
    vFunction.push_back(&apiGetVolumePathName);
    vFunction.push_back(&apiSetVolumeLabel);

    vFunction.push_back(&apiCloseHandle);
    vFunction.push_back(&apiFindClose);
}

void GetUtilityFunctions(__out std::vector<ApiFunction *>& vFunction)
{
    vFunction.clear();

    vFunction.push_back(&uCreateDirectory);
    vFunction.push_back(&uCreateDirectoryEx);
    vFunction.push_back(&uCreateDirectoryTransacted);
    vFunction.push_back(&uFindCloseChangeNotification);
    vFunction.push_back(&uFindFirstChangeNotification);
    vFunction.push_back(&uFindNextChangeNotification);
    vFunction.push_back(&uGetCurrentDirectory);
    vFunction.push_back(&uReadDirectoryChangesW);
    vFunction.push_back(&uRemoveDirectory);
    vFunction.push_back(&uRemoveDirectoryTransacted);
    vFunction.push_back(&uSetCurrentDirectory);

    vFunction.push_back(&uCancelIo);
    vFunction.push_back(&uCancelIoEx);
    vFunction.push_back(&uCancelSynchronousIo);
    vFunction.push_back(&uCreateIoCompletionPort);
    vFunction.push_back(&uFlushFileBuffers);
    vFunction.push_back(&uGetQueuedCompletionStatus);
    vFunction.push_back(&uGetQueuedCompletionStatusEx);
    vFunction.push_back(&uLockFile);
    vFunction.push_back(&uLockFileEx);
    vFunction.push_back(&uPostQueuedCompletionStatus);
    vFunction.push_back(&uReadFile);
    vFunction.push_back(&uWriteFile);
    vFunction.push_back(&uReadFileEx);
    vFunction.push_back(&uReadFileScatter);
    vFunction.push_back(&uSetEndOfFile);
    vFunction.push_back(&uSetFilePointerEx);
    vFunction.push_back(&uSetFileCompletionNotificationModes);
    vFunction.push_back(&uSetFileIoOverlappedRange);
    vFunction.push_back(&uSetFilePointer);
    vFunction.push_back(&uUnlockFile);
    vFunction.push_back(&uUnlockFileEx);
    vFunction.push_back(&uWriteFileEx);
    vFunction.push_back(&uWriteFileGather);

    vFunction.push_back(&uCopyFile);
    vFunction.push_back(&uCopyFileEx);
    vFunction.push_back(&uCreateFile);
    vFunction.push_back(&uDeleteFile);
    vFunction.push_back(&uFindFirstFile);
    vFunction.push_back(&uFindNextFile);
    vFunction.push_back(&uFindFirstFileEx);
    vFunction.push_back(&uFindFirstFileNameW);
    vFunction.push_back(&uFindFirstStreamW);
    vFunction.push_back(&uFindNextStreamW);
    vFunction.push_back(&uGetBinaryType);
    vFunction.push_back(&uGetCompressedFileSize);
    vFunction.push_back(&uGetFileAttributes);
    vFunction.push_back(&uGetFileAttributesEx);
    vFunction.push_back(&uGetFileInformationByHandle);
    vFunction.push_back(&uGetFileInformationByHandleEx);
    vFunction.push_back(&uGetFileSize);
    vFunction.push_back(&uGetFileSizeEx);
    vFunction.push_back(&uGetFileType);
    vFunction.push_back(&uGetFinalPathNameByHandle);
    vFunction.push_back(&uSetFileAttributes);
    vFunction.push_back(&uGetFullPathName);
    vFunction.push_back(&uGetLongPathName);
    vFunction.push_back(&uGetShortPathName);
    vFunction.push_back(&uGetTempFileName);
    vFunction.push_back(&uGetTempPath);
    vFunction.push_back(&uMoveFile);
    vFunction.push_back(&uMoveFileEx);
    vFunction.push_back(&uMoveFileWithProgress);
    vFunction.push_back(&uReplaceFile);
    vFunction.push_back(&uSearchPath);
    vFunction.push_back(&uSetFileInformationByHandle);
    vFunction.push_back(&uSetFileValidData);

    vFunction.push_back(&uGetDiskFreeSpace);
    vFunction.push_back(&uGetDiskFreeSpaceEx);

    vFunction.push_back(&uFindFirstVolume);
    vFunction.push_back(&uFindNextVolume);
    vFunction.push_back(&uFindVolumeClose);
    vFunction.push_back(&uQueryDosDevice);
    vFunction.push_back(&uGetVolumePathNamesForVolumeName);
    vFunction.push_back(&uGetVolumeNameForVolumeMountPoint);
    vFunction.push_back(&uFindFirstVolumeMountPoint);
    vFunction.push_back(&uFindNextVolumeMountPoint);
    vFunction.push_back(&uFindVolumeMountPointClose);
    vFunction.push_back(&uGetDriveType);
    vFunction.push_back(&uGetLogicalDrives);
    vFunction.push_back(&uGetLogicalDriveStrings);
    vFunction.push_back(&uGetVolumeInformation);
    vFunction.push_back(&uGetVolumeInformationByHandleW);
    vFunction.push_back(&uGetVolumePathName);
    vFunction.push_back(&uSetVolumeLabel);

    vFunction.push_back(&uCloseHandle);
    vFunction.push_back(&uFindClose);
}

void AllApiFunctionTest()
{
    Test_CreateFile_All();
    Test_CopyFile_All();
    Test_CopyFileEx_All();
    Test_MoveFile_All();
    Test_MoveFileEx_All(); //테스트 수행을 잘 하지만 너무 오래 걸린다. bizhard ICFS에서 모든 테스트에 통과.
    Test_MoveDirectory_All();
    Test_DeleteFile_All(); //테스트 수행을 잘 하지만 너무 오래 걸린다. bizhard ICFS에서 모든 테스트에 통과.
    Test_SetFileInformationByHandleAll();
    Test_GetFinalPathNameByHandleAll();  
    Test_GetFileSizeEx();
    Test_GetFileSize();
    Test_GetFileType();
    //Test_GetCurrentDirectory();
    Test_SetFileAttributesAll(); //테스트 수행을 잘 하지만 너무 오래 걸린다. bizhard ICFS에서 모든 테스트에 통과.
    Test_CreateAndRemoveDirecotryAll();
    //Test_GetVolumeInformationAll();
    Test_CreateDirectoryExAll(); //테스트 수행을 잘 하지만 너무 오래 걸린다. bizhard ICFS에서 모든 테스트에 통과.
    //Test_WriteFileAll();

    /*Test_WriteAndGetFileSize2();
    Test_SetEndOfFileAndGetFileSize2();
    Test_WriteFileAndGetDiskFreeSpace();
    Test_TruncateFileAndGetDiskFreeSpace();
    Test_SetFileTimeAll();
    Test_SetFileInformationByHandleAll();
    Test_GetFileSizeExAll();
    Test_SetEndOfFile_All();
    Test_GetDiskFreeSpaceAll();*/

    //Test_FindFirstFile_All();
    //Test_GetDiskFreeSpaceAll();
    //Test_GetDiskFreeSpaceEx_AllRootPath();
    //Test_FindFirstVolume_All();
    //Test_GetLogicalDrives();
    //Test_GetLogicalDriveStrings();
    //Test_GetDriveTypeAll();
    //Test_GetShortPathName();
    //Test_GetLongPathNameAll();
    //Test_GetCompressedFileSize();

    /*Test_CreateFileMapping_All();
    Test_SearchPath_Basic();
    Test_SetEndOfFile_Grow();*/
    //Test_FindFirstFileNameW();
    //Test_ReadWriteFileNormal();
}

void PrintApiStatistics(const std::vector<ApiFunction *>& vFunction)
{
    for_each(vFunction.begin(), vFunction.end(), mem_fun(&ApiFunction::PrintStatistics));
}

int _tmain(int argc, TCHAR* argv[])
{
    std::wcout.imbue(std::locale("korean"));

    if(argc > 1 && argv[1])
    {
        if(!IsFileExist(argv[1]))
        {
            CreateSubDir(argv[1]);
        }

        if(!SetBasePath(argv[1]))
        {
            return EXIT_FAILURE;
        }
    }
    else
    {
        if(!SetBasePath(L"D:\\"))
        {
            return EXIT_FAILURE;
        }
    }

    options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce a help screen")
        ("version,v", "print the version number")
        ("duration,d", "print the api duration")
        ("time,t", "print the output with time as prefix of lines")
        ("case,c", boost::program_options::value< size_t >(), "Run only the specified case.")
        ("statistics,s", "print api statistics")
        ("full-log,f", "print everything include utility functors.")
        ("io-test,i", "The program will run only for testing io performance.")
        ("createfile-test,r", "The program will run only for testing createfile.")
        ("filelist-test,l", "The program will run only for testing filelist.")
        ("openfile-test,o", "The program will run only for testing open files.")
        ("starttime", boost::program_options::value< std::string >(), "The program will run on specified time.")
        ("endtime", boost::program_options::value< std::string >(), "The program will run on specified time.")
        ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);

    std::vector<ApiFunction *> vFunction;
    GetFunctions(vFunction);

    std::vector<ApiFunction *> vUtilityFunction;
    GetUtilityFunctions(vUtilityFunction);

    if(vm.count("help"))
    {
        cout << "Usage: regex [options]\n";
        cout << desc;
        return 0;
    }
    if(vm.count("version"))
    {
        cout << "Version 1.\n";
        return 0;
    }
    if(vm.count("starttime") && vm.count("endtime"))
    {
        cout << "The program will run during the specific time. " << vm["starttime"].as<std::string>() << " ~ " << vm["endtime"].as<std::string>() << std::endl;
        std::string starttime = vm["starttime"].as<std::string>();
        std::string endtime = vm["endtime"].as<std::string>();

        assert(starttime.size() == 8 && endtime.size() == 8);
        char t[3] = { 0 };

        t[0] = starttime[0];
        t[1] = starttime[1];
        TestLog::starttime_.wHour = (WORD)atoi(t);

        t[0] = starttime[3];
        t[1] = starttime[4];
        TestLog::starttime_.wMinute = (WORD)atoi(t);

        t[0] = starttime[6];
        t[1] = starttime[7];
        TestLog::starttime_.wSecond = (WORD)atoi(t);


        t[0] = endtime[0];
        t[1] = endtime[1];
        TestLog::endtime_.wHour = (WORD)atoi(t);

        t[0] = endtime[3];
        t[1] = endtime[4];
        TestLog::endtime_.wMinute = (WORD)atoi(t);

        t[0] = endtime[6];
        t[1] = endtime[7];
        TestLog::endtime_.wSecond = (WORD)atoi(t);

        TestLog::fUseTimer_ = true;
    }
    if(vm.count("duration"))
    {
        cout << "The configuration was set to print duration.\n";
        for_each(vFunction.begin(), vFunction.end(), bind2nd(mem_fun(&ApiFunction::EnableDurationOutput), true));
    }
    if(vm.count("time"))
    {
        cout << "The configuration was set to print time.\n";
        for_each(vFunction.begin(), vFunction.end(), bind2nd(mem_fun(&ApiFunction::EnableDateTimeOutput), true));
    }
    if (vm.count("case"))
    {
        cout << "The configuration was set to run specific case.\n";
        TestLog::SetSpecificCase(vm["case"].as<size_t>());
    }
    if (vm.count("statistics"))
    {
        cout << "The configuration was set to print api statistics.\n";
    }
    if(vm.count("full-log") == 0)
    {
        for_each(vUtilityFunction.begin(), vUtilityFunction.end(), bind2nd(mem_fun(&ApiFunction::EnableLog), false));
    }
    if(vm.count("io-test"))
    {
        ApiStatistics st;
        PTEST(FILE_IO, &st);
    }
    else if(vm.count("createfile-test"))
    {
        ApiStatistics st;
        PTEST(CREATE_AND_DELETE_FILES/*_DEEP*/, &st);
    }
    else if(vm.count("filelist-test"))
    {
        ApiStatistics st;
        PTEST(GET_FILE_LIST, &st);
    }
    else if(vm.count("openfile-test"))
    {
        ApiStatistics st;
        PTEST(OPEN_FILE, &st);
    }
    else
    {
        AllApiFunctionTest();
    }

    // 맨 밑에 둘것
    if (vm.count("statistics"))
    {
        PrintApiStatistics(vFunction);
    }
    if(vm.count("full-log"))
    {
        PrintApiStatistics(vUtilityFunction);
    }

    return EXIT_SUCCESS;
}