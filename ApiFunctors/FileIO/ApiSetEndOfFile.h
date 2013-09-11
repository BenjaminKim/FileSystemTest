#pragma once


DEFINE_API_CLASS_BEGIN(SetEndOfFile)

BOOL operator()(__in  HANDLE hFile)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(BOOL, SetEndOfFile,
        hFile);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()