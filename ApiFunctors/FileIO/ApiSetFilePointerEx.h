#pragma once

#include "ApiSetFilePointer.h"


DEFINE_API_CLASS_BEGIN(SetFilePointerEx)

static std::wstring GetString_dwMoveMethod(DWORD dwMoveMethod)
{
    return ApiSetFilePointer::GetString_dwMoveMethod(dwMoveMethod);
}

BOOL operator()(
    __in       HANDLE hFile,
    __in       LARGE_INTEGER liDistanceToMove,
    __out_opt  PLARGE_INTEGER lpNewFilePointer,
    __in       DWORD dwMoveMethod)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(LARGE_INTEGER, liDistanceToMove);
    ADD_IN_PARAM(_dwMoveMethod, dwMoveMethod);

    API_CALL_T(BOOL, SetFilePointerEx,
        hFile,
        liDistanceToMove,
        lpNewFilePointer,
        dwMoveMethod);

    ADD_OUT_PARAM(PLARGE_INTEGER, lpNewFilePointer);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()