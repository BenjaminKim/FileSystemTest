#include "stdafx.h"
#include "TestWNetEnumResource.h"
#include "WindowsNetworking/ApiWNetOpenEnum.h"
#include "WindowsNetworking/ApiWNetEnumResource.h"
#include "WindowsNetworking/ApiWNetCloseEnum.h"

using namespace std;

void Test_WNetEnumResource()
{
    DEF_TESTLOG_T("Test_WNetEnumResource");
    ApiWNetOpenEnumW apiWNetOpenEnumW;
    ApiWNetEnumResourceW apiWNetEnumResourceW;
    ApiWNetCloseEnum apiWNetCloseEnum;

    HANDLE hEnum = INVALID_HANDLE_VALUE;

    DWORD error = apiWNetOpenEnumW(
        RESOURCE_CONNECTED,
        RESOURCETYPE_ANY,
        0,
        0,
        &hEnum);

    if(error == NO_ERROR)
    {
        for(;;)
        {
            NETRESOURCE netRes[100];
            DWORD count = 100;
            DWORD size = sizeof(netRes);
            error = apiWNetEnumResourceW(hEnum, &count, &netRes, &size);

            if(error == NO_ERROR)
            {
                continue;
            }

            if(error == ERROR_MORE_DATA)
            {
                continue;
            }

            if(error == ERROR_NO_MORE_ITEMS)
            {
                break;
            }

            log.GetStream(TestLog::MT_ERROR) << L"WNetEnumResourceW Fail. ErrorCode = " << error << endl;
            break;
        }

        apiWNetCloseEnum(hEnum);
    }
    else
    {
        log.GetStream(TestLog::MT_ERROR) << L"WNetOpenEnum Fail. ErrorCode = " << error << endl;
    }

    log.Ok();
}