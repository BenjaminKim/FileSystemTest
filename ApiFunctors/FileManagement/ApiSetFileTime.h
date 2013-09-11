#pragma once


DEFINE_API_CLASS_BEGIN(SetFileTime)

BOOL operator()(
                __in      HANDLE hFile,
                __in_opt  const FILETIME *lpCreationTime,
                __in_opt  const FILETIME *lpLastAccessTime,
                __in_opt  const FILETIME *lpLastWriteTime)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(_FileTime, lpCreationTime);
    ADD_IN_PARAM(_FileTime, lpLastAccessTime);
    ADD_IN_PARAM(_FileTime, lpLastWriteTime);

    API_CALL_T(BOOL, SetFileTime,
        hFile,
        lpCreationTime,
        lpLastAccessTime,
        lpLastWriteTime);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()