#pragma once


DEFINE_API_CLASS_BEGIN(SetFilePointer)

static std::wstring GetString_dwMoveMethod(DWORD dwMoveMethod)
{
    SWITCH_BEGIN(dwMoveMethod)
        CASE(FILE_BEGIN)
        CASE(FILE_CURRENT)
        CASE(FILE_END)
    SWITCH_END()
}

DWORD operator()(
    __in        HANDLE hFile,
    __in        LONG lDistanceToMove,
    __inout_opt PLONG lpDistanceToMoveHigh,
    __in        DWORD dwMoveMethod)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(LONG, lDistanceToMove);
    ADD_IN_PARAM(PLONG, lpDistanceToMoveHigh);
    ADD_IN_PARAM(_dwMoveMethod, dwMoveMethod);

    API_CALL_T(DWORD, SetFilePointer,
        hFile,
        lDistanceToMove,
        lpDistanceToMoveHigh,
        dwMoveMethod);

    ADD_OUT_PARAM(PLONG, lpDistanceToMoveHigh);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()