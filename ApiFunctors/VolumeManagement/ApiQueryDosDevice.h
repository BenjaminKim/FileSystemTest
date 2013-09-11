#pragma once


DEFINE_API_CLASS_BEGIN(QueryDosDevice)

DWORD operator()(
    __in_opt LPCWSTR lpDeviceName,
    __out_ecount_part_opt(ucchMax, return) LPWSTR lpTargetPath,
    __in     DWORD ucchMax)
{
    ADD_IN_PARAM(PSTR, lpDeviceName);
    ADD_IN_PARAM(DWORD, ucchMax);

    API_CALL_T(DWORD, QueryDosDeviceW,
        lpDeviceName,
        lpTargetPath,
        ucchMax);

    ADD_OUT_PARAM(PSTR, lpTargetPath);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()