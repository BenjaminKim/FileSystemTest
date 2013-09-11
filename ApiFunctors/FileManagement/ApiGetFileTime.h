#pragma once


DEFINE_API_CLASS_BEGIN(GetFileTime)

BOOL operator()(
                __in       HANDLE hFile,
                __out_opt  LPFILETIME lpCreationTime,
                __out_opt  LPFILETIME lpLastAccessTime,
                __out_opt  LPFILETIME lpLastWriteTime)
{
    ADD_IN_PARAM(HANDLE, hFile);
    
    API_CALL_T(BOOL, GetFileTime,
        hFile,
        lpCreationTime,
        lpLastAccessTime,
        lpLastWriteTime);

    ADD_OUT_PARAM(_FileTime, lpCreationTime);
    ADD_OUT_PARAM(_FileTime, lpLastAccessTime);
    ADD_OUT_PARAM(_FileTime, lpLastWriteTime);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()