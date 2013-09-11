#pragma once

DEFINE_API_CLASS_BEGIN(WNetCloseEnum)

DWORD operator()(
                 __in  HANDLE hEnum)
{
    ADD_IN_PARAM(HANDLE, hEnum);

    API_CALL_T(DWORD, WNetCloseEnum,
        hEnum);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()