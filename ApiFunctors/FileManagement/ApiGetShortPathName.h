#pragma once


DEFINE_API_CLASS_BEGIN(GetShortPathName)

DWORD operator()(
    __in   LPCTSTR lpszLongPath,
    __out  LPTSTR lpszShortPath,
    __in   DWORD cchBuffer)
{
    ADD_IN_PARAM(PSTR, lpszLongPath);
    ADD_IN_PARAM(DWORD, cchBuffer);

    API_CALL_T(DWORD, GetShortPathName,
        lpszLongPath,
        lpszShortPath,
        cchBuffer);

    ADD_OUT_PARAM(PSTR, lpszShortPath);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()