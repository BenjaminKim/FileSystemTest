#pragma once


DEFINE_API_CLASS_BEGIN(FindClose)

BOOL operator()(
                __inout  HANDLE hFindFile)
{
    ADD_IN_PARAM(HANDLE, hFindFile);

    API_CALL_T(BOOL, FindClose,
        hFindFile);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()