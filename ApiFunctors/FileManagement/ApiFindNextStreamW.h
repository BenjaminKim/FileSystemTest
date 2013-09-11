#pragma once


DEFINE_API_CLASS_BEGIN(FindNextStreamW)

BOOL operator()(
    __in   HANDLE hFindStream,
    __out  LPVOID lpFindStreamData)
{
    ADD_IN_PARAM(HANDLE, hFindStream);

    API_CALL_T(BOOL, FindNextStreamW,
        hFindStream,
        lpFindStreamData);

    ADD_OUT_PARAM(PVOID, lpFindStreamData);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()