#pragma once

void CreateManyFiles_And_DeleteTheFiles(size_t iFileNum);
void CreateManyFiles_And_DeleteTheFiles_Deep(size_t iFileNum);
void CreateSomeFiles_And_ListTheFiles(size_t iFileNum);
void WriteFileTest(size_t sizeKB, size_t bufferSize, ApiStatistics* pStatistics);
void ReadFileTest(size_t sizeKB, size_t bufferSize, ApiStatistics* pStatistics);
void OpenCloseFileTest(size_t fileNum, size_t loopCount);
void CreateSomeFiles_And_ListTheFiles(size_t fileNum, size_t loopCount, ApiStatistics* pStatistics);

enum TESTCASE
{
    CREATE_AND_DELETE_FILES = 0,
    FILE_IO = 1,
    GET_FILE_LIST = 2,
    OPEN_FILE = 3,
    CREATE_AND_DELETE_FILES_DEEP = 4
};

inline void PTEST(TESTCASE tc, ApiStatistics* pStatistics)
{
    switch(tc)
    {
    case CREATE_AND_DELETE_FILES:
        CreateManyFiles_And_DeleteTheFiles(10000000);
        break;
    case CREATE_AND_DELETE_FILES_DEEP:
        CreateManyFiles_And_DeleteTheFiles_Deep(50);
        break;
    case FILE_IO:
        WriteFileTest(500* 1024, 1024, pStatistics);
        //ReadFileTest(500 * 1024 * 1024, 1024, pStatistics);
        break;
    case GET_FILE_LIST:
        CreateSomeFiles_And_ListTheFiles(50, 10000000, pStatistics);
        break;
    case OPEN_FILE:
        OpenCloseFileTest(30, 10000000);
        break;
    default:
        break;
    }
}