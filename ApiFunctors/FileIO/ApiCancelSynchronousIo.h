#pragma once


DEFINE_API_CLASS_BEGIN(CancelSynchronousIo)

BOOL operator()(
    __in  HANDLE hThread)
{
    ADD_IN_PARAM(HANDLE, hThread);

    API_CALL_T(BOOL, CancelSynchronousIo,
        hThread);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()