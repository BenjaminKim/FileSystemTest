#pragma once


DEFINE_API_CLASS_BEGIN(DeleteFile)

BOOL operator()(__in LPCTSTR lpFileName)
{
    ADD_IN_PARAM(PSTR, lpFileName);

    API_CALL_T(BOOL, DeleteFileW,
        lpFileName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()