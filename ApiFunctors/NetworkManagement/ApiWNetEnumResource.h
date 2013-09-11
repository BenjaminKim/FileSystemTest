#pragma once


DEFINE_API_CLASS_BEGIN(WNetEnumResource)

static std::wstring GetString_lpBuffer(PVOID lpBuffer)
{
    if(lpBuffer == 0)
    {
        return L"EMPTY\n";
    }

    LPNETRESOURCEW lpnrLocal = (LPNETRESOURCEW)lpBuffer;
    std::wostringstream oss;

    oss << L"NETRESOURCE[%d] Scope: ";
    switch (lpnrLocal->dwScope) {
    case (RESOURCE_CONNECTED):
        oss << L"connected\n";
        break;
    case (RESOURCE_GLOBALNET):
        oss << L"all resources\n";
        break;
    case (RESOURCE_REMEMBERED):
        oss << L"remembered\n";
        break;
    default:
        oss << L"unknown scope " << lpnrLocal->dwScope << std::endl;
        break;
    }

    oss << L"NETRESOURCE[%d] Type: ";
    switch (lpnrLocal->dwType)
    {
    case (RESOURCETYPE_ANY):
        oss << L"any\n";
        break;
    case (RESOURCETYPE_DISK):
        oss << L"disk\n";
        break;
    case (RESOURCETYPE_PRINT):
        oss << L"print\n";
        break;
    default:
        oss << L"unknown type %d\n", lpnrLocal->dwType;
        break;
    }

    oss << L"NETRESOURCE[%d] DisplayType: ";
    switch (lpnrLocal->dwDisplayType)
    {
    case (RESOURCEDISPLAYTYPE_GENERIC):
        oss << L"generic\n";
        break;
    case (RESOURCEDISPLAYTYPE_DOMAIN):
        oss << L"domain\n";
        break;
    case (RESOURCEDISPLAYTYPE_SERVER):
        oss << L"server\n";
        break;
    case (RESOURCEDISPLAYTYPE_SHARE):
        oss << L"share\n";
        break;
    case (RESOURCEDISPLAYTYPE_FILE):
        oss << L"file\n";
        break;
    case (RESOURCEDISPLAYTYPE_GROUP):
        oss << L"group\n";
        break;
    case (RESOURCEDISPLAYTYPE_NETWORK):
        oss << L"network\n";
        break;
    default:
        oss << L"unknown display type %d\n", lpnrLocal->dwDisplayType;
        break;
    }

    oss << L"NETRESOURCE[] Usage: " << lpnrLocal->dwUsage << L" = ";
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONNECTABLE)
        oss << L"connectable ";
    if (lpnrLocal->dwUsage & RESOURCEUSAGE_CONTAINER)
        oss << L"container ";
    oss << L"\n";

    oss << L"NETRESOURCE[%d] Localname: " << lpnrLocal->lpLocalName << std::endl;
    oss << L"NETRESOURCE[%d] Remotename: " << lpnrLocal->lpRemoteName << std::endl;
    oss << L"NETRESOURCE[%d] Comment: " << lpnrLocal->lpComment << std::endl;
    oss << L"NETRESOURCE[%d] Provider: " << lpnrLocal->lpProvider << std::endl;
    oss << L"\n";

    return oss.str();
}

DWORD operator()(
                 __in     HANDLE hEnum,
                 __inout  LPDWORD lpcCount,
                 __out    LPVOID lpBuffer,
                 __inout  LPDWORD lpBufferSize)
{
    ADD_IN_PARAM(HANDLE, hEnum);
    ADD_IN_PARAM(PDWORD, lpcCount);
    ADD_IN_PARAM(PDWORD, lpBufferSize);

    API_CALL_T(DWORD, WNetEnumResource,
        hEnum,
        lpcCount,
        lpBuffer,
        lpBufferSize);

    ADD_OUT_PARAM(PDWORD, lpcCount);
    ADD_OUT_PARAM(_lpBuffer, lpBuffer);
    ADD_OUT_PARAM(PDWORD, lpBufferSize);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()