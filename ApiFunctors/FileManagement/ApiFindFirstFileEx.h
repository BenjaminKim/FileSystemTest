#pragma once


DEFINE_API_CLASS_BEGIN(FindFirstFileEx)

static std::wstring GetString_fInfoLevelId(FINDEX_INFO_LEVELS fInfoLevelId)
{
    SWITCH_BEGIN(fInfoLevelId)
        CASE(FindExInfoStandard)
        CASE(FindExInfoMaxInfoLevel)
    SWITCH_END()
}

static std::wstring GetString_fSearchOp(FINDEX_SEARCH_OPS fSearchOp)
{
    SWITCH_BEGIN(fSearchOp)
        CASE(FindExSearchNameMatch)
        CASE(FindExSearchLimitToDirectories)
        CASE(FindExSearchLimitToDevices)
        CASE(FindExSearchMaxSearchOp)
    SWITCH_END()
}

static std::wstring GetString_dwAdditionalFlags(DWORD dwAdditionalFlags)
{
    SWITCH_BEGIN(dwAdditionalFlags)
        CASE(FIND_FIRST_EX_CASE_SENSITIVE)
    SWITCH_END()
}

HANDLE operator()(
    __in        LPCTSTR lpFileName,
    __in        FINDEX_INFO_LEVELS fInfoLevelId,
    __out       LPVOID lpFindFileData,
    __in        FINDEX_SEARCH_OPS fSearchOp,
    __reserved  LPVOID lpSearchFilter,
    __in        DWORD dwAdditionalFlags)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(_fInfoLevelId, fInfoLevelId);
    ADD_IN_PARAM(_fSearchOp, fSearchOp);
    ADD_IN_PARAM(PVOID, lpSearchFilter);
    ADD_IN_PARAM(_dwAdditionalFlags, dwAdditionalFlags);

    API_CALL_T(HANDLE, FindFirstFileExW,
        lpFileName,
        fInfoLevelId,
        lpFindFileData,
        fSearchOp,
        lpSearchFilter,
        dwAdditionalFlags);

    ADD_OUT_PARAM(PVOID, lpFindFileData);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()