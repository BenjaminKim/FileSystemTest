#pragma once


DEFINE_API_CLASS_BEGIN(WNetOpenEnum)

static std::wstring GetString_LPNETRESOURCE(LPNETRESOURCE lpNetResource)
{
    std::wostringstream oss;

    oss << _T("lpLocalName -> ") << lpNetResource->lpLocalName << std::endl;
    oss << _T("lpRemoteName -> ") << lpNetResource->lpLocalName << std::endl;
    oss << _T("lpComment -> ") << lpNetResource->lpLocalName << std::endl;
    oss << _T("lpProvider -> ") << lpNetResource->lpLocalName << std::endl;
    oss << _T("dwScope -> ") << lpNetResource->dwScope << std::endl;
    oss << _T("dwType -> ") << lpNetResource->dwType << std::endl;
    oss << _T("dwDisplayType -> ") << lpNetResource->dwDisplayType << std::endl;
    oss << _T("dwUsage -> ") << lpNetResource->dwUsage << std::endl;

    return oss.str();
}

std::wstring GetString_PHANDLE(LPHANDLE lphEnum)
{
    return GetStringHANDLE(lphEnum);
}

DWORD operator()(
                 __in   DWORD dwScope,
                 __in   DWORD dwType,
                 __in   DWORD dwUsage,
                 __in   LPNETRESOURCE lpNetResource,
                 __out  LPHANDLE lphEnum)
{
    ADD_IN_PARAM(DWORD, dwScope);
    ADD_IN_PARAM(DWORD, dwType);
    ADD_IN_PARAM(DWORD, dwUsage);
    ADD_IN_PARAM(_LPNETRESOURCE, lpNetResource);

    API_CALL_T(DWORD, WNetOpenEnum,
        dwScope,
        dwType,
        dwUsage,
        lpNetResource,
        lphEnum);

    ADD_OUT_PARAM(_PHANDLE, lphEnum);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()