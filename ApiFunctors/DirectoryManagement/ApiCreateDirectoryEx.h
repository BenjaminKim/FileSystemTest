#pragma once


DEFINE_API_CLASS_BEGIN(CreateDirectoryEx)

BOOL operator()(
    __in      LPCTSTR lpTemplateDirectory,
    __in      LPCTSTR lpNewDirectory,
    __in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
    ADD_IN_PARAM(PSTR, lpTemplateDirectory);
    ADD_IN_PARAM(PSTR, lpNewDirectory);
    ADD_IN_PARAM(PVOID, lpSecurityAttributes);

    API_CALL_T(BOOL, CreateDirectoryEx,
        lpTemplateDirectory,
        lpNewDirectory,
        lpSecurityAttributes);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()