#pragma once


DEFINE_API_CLASS_BEGIN(CreateDirectory)

BOOL operator()(
    __in      LPCTSTR lpPathName,
    __in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    ADD_IN_PARAM(PSTR, lpPathName);
    ADD_IN_PARAM(PVOID, lpSecurityAttributes);

    API_CALL_T(BOOL, CreateDirectory,
        lpPathName,
        lpSecurityAttributes);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()