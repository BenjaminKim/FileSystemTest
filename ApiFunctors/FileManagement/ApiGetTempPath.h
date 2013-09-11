#pragma once


DEFINE_API_CLASS_BEGIN(GetTempPath)

DWORD operator()(
    __in   DWORD nBufferLength,
    __out  LPTSTR lpBuffer)
{
    ADD_IN_PARAM(DWORD, nBufferLength);

    API_CALL_T(DWORD, GetTempPathW,
        nBufferLength,
        lpBuffer);

    ADD_OUT_PARAM(PSTR, lpBuffer);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()