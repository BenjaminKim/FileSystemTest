#pragma once


DEFINE_API_CLASS_BEGIN(FindNextChangeNotification)

BOOL operator()(
    __in  HANDLE hChangeHandle)
{
    ADD_IN_PARAM(HANDLE, hChangeHandle);

    API_CALL_T(BOOL, FindNextChangeNotification,
        hChangeHandle);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()