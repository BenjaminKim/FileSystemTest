#pragma once


DEFINE_API_CLASS_BEGIN(RemoveDirectoryTransacted)

BOOL operator()(
    __in  LPCTSTR lpPathName,
    __in  HANDLE hTransaction)
{
    ADD_IN_PARAM(PSTR, lpPathName);
    ADD_IN_PARAM(HANDLE, hTransaction);

    API_CALL_T(BOOL, RemoveDirectoryTransacted,
        lpPathName,
        hTransaction);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()