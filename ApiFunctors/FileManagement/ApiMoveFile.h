#pragma once


DEFINE_API_CLASS_BEGIN(MoveFile)

BOOL operator()(
    __in LPCWSTR lpExistingFileName,
    __in LPCWSTR lpNewFileName)
{
    ADD_IN_PARAM(PSTR, lpExistingFileName);
    ADD_IN_PARAM(PSTR, lpNewFileName);

    API_CALL_T(BOOL, MoveFileW,
        lpExistingFileName,
        lpNewFileName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()