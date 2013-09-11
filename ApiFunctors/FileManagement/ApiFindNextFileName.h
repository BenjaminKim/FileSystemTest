#pragma once


DEFINE_API_CLASS_BEGIN(FindNextFileNameW)

BOOL operator()(
    __in     HANDLE hFindStream,
    __inout  LPDWORD StringLength,
    __inout  PWCHAR LinkName)
{
    ADD_IN_PARAM(HANDLE, hFindStream);
    ADD_IN_PARAM(PDWORD, StringLength);
    ADD_IN_PARAM(PSTR, LinkName);

    API_CALL_T(BOOL, FindNextFileNameW,
        hFindStream,
        StringLength,
        LinkName);

    ADD_OUT_PARAM(PDWORD, StringLength);
    ADD_OUT_PARAM(PSTR, LinkName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()