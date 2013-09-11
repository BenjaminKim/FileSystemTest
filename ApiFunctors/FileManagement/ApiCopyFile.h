#pragma once


DEFINE_API_CLASS_BEGIN(CopyFile)

BOOL operator()(
    __in  LPCTSTR lpExistingFileName,
    __in  LPCTSTR lpNewFileName,
    __in  BOOL bFailIfExists)
{
    ADD_IN_PARAM(PSTR, lpExistingFileName);
    ADD_IN_PARAM(PSTR, lpNewFileName);
    ADD_IN_PARAM(BOOL, bFailIfExists);

    API_CALL_T(BOOL, CopyFileW,
        lpExistingFileName,
        lpNewFileName,
        bFailIfExists);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()