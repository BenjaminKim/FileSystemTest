#pragma once


DEFINE_API_CLASS_BEGIN(GetTempFileName)

DWORD operator()(
    __in   LPCTSTR lpPathName,
    __in   LPCTSTR lpPrefixString,
    __in   UINT uUnique,
    __out  LPTSTR lpTempFileName)
{
    ADD_IN_PARAM(PSTR, lpPathName);
    ADD_IN_PARAM(PSTR, lpPrefixString);
    ADD_IN_PARAM(UINT32, uUnique);

    API_CALL_T(DWORD, GetTempFileName,
        lpPathName,
        lpPrefixString,
        uUnique,
        lpTempFileName);

    ADD_OUT_PARAM(PSTR, lpTempFileName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()