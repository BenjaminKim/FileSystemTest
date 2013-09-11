#pragma once

// Windows Vista
DEFINE_API_CLASS_BEGIN(CreateDirectoryTransacted)

BOOL operator()(
    __in_opt  LPCTSTR lpTemplateDirectory,
    __in      LPCTSTR lpNewDirectory,
    __in_opt  LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    __in      HANDLE hTransaction)
{
    ADD_IN_PARAM(PSTR, lpTemplateDirectory);
    ADD_IN_PARAM(PSTR, lpNewDirectory);
    ADD_IN_PARAM(PVOID, lpSecurityAttributes);
    ADD_IN_PARAM(HANDLE, hTransaction);

    API_CALL_T(BOOL, CreateDirectoryTransacted,
        lpTemplateDirectory,
        lpNewDirectory,
        lpSecurityAttributes,
        hTransaction);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()
