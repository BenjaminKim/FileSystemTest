#pragma once


DEFINE_API_CLASS_BEGIN(CloseHandle)

BOOL operator()(
                __in  HANDLE hObject)
{
    ADD_IN_PARAM(HANDLE, hObject);

    API_CALL_T(BOOL, CloseHandle,
        hObject);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()