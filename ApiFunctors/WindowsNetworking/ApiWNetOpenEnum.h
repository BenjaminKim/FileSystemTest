#pragma once


DEFINE_API_CLASS_DYN_BEGIN(WNetOpenEnumW, Mpr.dll)

static std::wstring GetString_dwScope(DWORD dwScope)
{
    SWITCH_BEGIN(dwScope)
        CASE(RESOURCE_CONNECTED)
        CASE(RESOURCE_GLOBALNET)
        CASE(RESOURCE_REMEMBERED)
        CASE(RESOURCE_RECENT)
        CASE(RESOURCE_CONTEXT)
    SWITCH_END()
}

static std::wstring GetString_dwType(DWORD dwType)
{
    SWITCH_BEGIN(dwType)
        CASE(RESOURCETYPE_ANY)
        CASE(RESOURCETYPE_DISK)
        CASE(RESOURCETYPE_PRINT)
        CASE(RESOURCETYPE_RESERVED)
        CASE(RESOURCETYPE_UNKNOWN)
    SWITCH_END()
}

static std::wstring GetString_dwUsage(DWORD dwUsage)
{
    CHECK_BIT_BEGIN_HEX(dwUsage)

    CHECK_BIT_CLEAR(RESOURCEUSAGE_ALL)
    CHECK_BIT(RESOURCEUSAGE_CONNECTABLE)
    CHECK_BIT(RESOURCEUSAGE_CONTAINER)
    CHECK_BIT(RESOURCEUSAGE_NOLOCALDEVICE)
    CHECK_BIT(RESOURCEUSAGE_SIBLING)
    CHECK_BIT(RESOURCEUSAGE_ATTACHED)

    CHECK_BIT_END()
}

static std::wstring GetString_dwDisplayType(DWORD dwDisplayType)
{
    SWITCH_BEGIN(dwDisplayType)
        CASE(RESOURCEDISPLAYTYPE_GENERIC)
        CASE(RESOURCEDISPLAYTYPE_DOMAIN)
        CASE(RESOURCEDISPLAYTYPE_SERVER)
        CASE(RESOURCEDISPLAYTYPE_SHARE)
        CASE(RESOURCEDISPLAYTYPE_FILE)
        CASE(RESOURCEDISPLAYTYPE_GROUP)
        CASE(RESOURCEDISPLAYTYPE_NETWORK)
        CASE(RESOURCEDISPLAYTYPE_ROOT)
        CASE(RESOURCEDISPLAYTYPE_SHAREADMIN)
        CASE(RESOURCEDISPLAYTYPE_DIRECTORY)
        CASE(RESOURCEDISPLAYTYPE_TREE)
        CASE(RESOURCEDISPLAYTYPE_NDSCONTAINER)
    SWITCH_END()
}

static std::wstring GetString_lpNetResource(LPNETRESOURCEW lpNetResource)
{
    if(lpNetResource)
    {
        std::wostringstream oss;

        oss << L"dwScope= " << GetString_dwScope(lpNetResource->dwScope) << L"," << std::endl;
        oss << L"dwType= " << GetString_dwType(lpNetResource->dwType) << L"," << std::endl;
        oss << L"dwDisplayType= " << GetString_dwDisplayType(lpNetResource->dwDisplayType) << L"," << std::endl;
        oss << L"dwUsage= " << GetString_dwUsage(lpNetResource->dwUsage) << L"," << std::endl;
        oss << L"lpLocalName= " << (lpNetResource->lpLocalName ? lpNetResource->lpLocalName : L"(NULL)") << L"," << std::endl;
        oss << L"lpRemoteName= " << (lpNetResource->lpRemoteName ? lpNetResource->lpRemoteName : L"(NULL)") << L"," << std::endl;
        oss << L"lpComment= " << (lpNetResource->lpComment ? lpNetResource->lpComment : L"(NULL)") << L"," << std::endl;
        oss << L"lpProvider= " << (lpNetResource->lpProvider ? lpNetResource->lpProvider : L"(NULL)");

        return oss.str();
    }

    return L"(NULL)";
}

DWORD operator()(
    __in  DWORD          dwScope,
    __in  DWORD          dwType,
    __in  DWORD          dwUsage,
    __in_opt LPNETRESOURCEW lpNetResource,
    __out LPHANDLE       lphEnum)
{
    ADD_IN_PARAM(_dwScope, dwScope);
    ADD_IN_PARAM(_dwType, dwType);
    ADD_IN_PARAM(_dwUsage, dwUsage);
    ADD_IN_PARAM(_lpNetResource, lpNetResource);

    API_DYN_CALL_T(DWORD, WNetOpenEnumW,
        dwScope,
        dwType,
        dwUsage,
        lpNetResource,
        lphEnum);

    ADD_OUT_PARAM(HANDLE, *lphEnum);

    API_RETURN_T();
}

DEFINE_API_CLASS_DYN_END(WNetOpenEnumW,
                         DWORD (__stdcall *)(
                         __in  DWORD          dwScope,
                         __in  DWORD          dwType,
                         __in  DWORD          dwUsage,
                         __in_opt LPNETRESOURCEW lpNetResource,
                         __out LPHANDLE       lphEnum)
                         )