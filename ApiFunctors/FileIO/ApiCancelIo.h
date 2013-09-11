#pragma once


DEFINE_API_CLASS_BEGIN(CancelIo)

BOOL operator()(
    __in  HANDLE hFile)
{
    ADD_IN_PARAM(HANDLE, hFile);

    API_CALL_T(BOOL, CancelIo,
        hFile);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()