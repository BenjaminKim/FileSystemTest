#pragma once


DEFINE_API_CLASS_BEGIN(GetLongPathName)

DWORD operator()(
    __in   LPCTSTR lpszShortPath,
    __out  LPTSTR lpszLongPath,
    __in   DWORD cchBuffer)
{
    ADD_IN_PARAM(PSTR, lpszShortPath);
    ADD_IN_PARAM(DWORD, cchBuffer);

    API_CALL_T(DWORD, GetLongPathName,
        lpszShortPath,
        lpszLongPath,
        cchBuffer);

    ADD_OUT_PARAM(PSTR, lpszLongPath);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()