#pragma once


DEFINE_API_CLASS_BEGIN(SetCurrentDirectory)

BOOL operator()(
    __in  LPCTSTR lpPathName)
{
    ADD_IN_PARAM(PSTR, lpPathName);

    API_CALL_T(BOOL, SetCurrentDirectory,
        lpPathName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()
