#pragma once


DEFINE_API_CLASS_BEGIN(SetFileAttributes)

BOOL operator()(
    __in  LPCTSTR lpFileName,
    __in  DWORD dwFileAttributes)
{
    ADD_IN_PARAM(PSTR, lpFileName);
    ADD_IN_PARAM(_dwFileAttributes, dwFileAttributes);      

    API_CALL_T(BOOL, SetFileAttributes,
        lpFileName,
        dwFileAttributes);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()