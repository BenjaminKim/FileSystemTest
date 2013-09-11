#pragma once


DEFINE_API_CLASS_BEGIN(GetVolumePathNamesForVolumeName)

static std::wstring GetString_lpszVolumePathNames(LPWCH lpszVolumePathNames)
{
    std::wostringstream oss;
    bool notFirst = false;

    oss << '[';
    for(PWCHAR nameIdx = lpszVolumePathNames;
        nameIdx[0] != L'\0';
        nameIdx += wcslen(nameIdx) + 1) 
    {
        if(notFirst)
        {
            oss << L", ";
        }
        else
        {
            notFirst = true;
        }
        oss << nameIdx;
    }
    oss << ']';

    return oss.str();
}

BOOL operator()(
    __in  LPCWSTR lpszVolumeName,
    __out_ecount_part_opt(cchBufferLength, *lpcchReturnLength) __nullnullterminated LPWCH lpszVolumePathNames,
    __in  DWORD cchBufferLength,
    __out PDWORD lpcchReturnLength)
{
    ADD_IN_PARAM(PSTR, lpszVolumeName);
    ADD_IN_PARAM(DWORD, cchBufferLength);

    API_CALL_T(BOOL, GetVolumePathNamesForVolumeNameW,
        lpszVolumeName,
        lpszVolumePathNames,
        cchBufferLength,
        lpcchReturnLength);

    if(returnValueT)
    {
        AddOutParam(L"lpszVolumePathNames", GetString_lpszVolumePathNames(lpszVolumePathNames));
    }
    ADD_OUT_PARAM(PDWORD, lpcchReturnLength);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()
