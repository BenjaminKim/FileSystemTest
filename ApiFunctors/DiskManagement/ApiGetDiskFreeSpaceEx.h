#pragma once


DEFINE_API_CLASS_BEGIN(GetDiskFreeSpaceEx)

BOOL operator()(
    __in_opt  LPCWSTR lpDirectoryName,
    __out_opt PULARGE_INTEGER lpFreeBytesAvailableToCaller,
    __out_opt PULARGE_INTEGER lpTotalNumberOfBytes,
    __out_opt PULARGE_INTEGER lpTotalNumberOfFreeBytes)
{
    ADD_IN_PARAM(PSTR, lpDirectoryName);

    API_CALL_T(BOOL, GetDiskFreeSpaceExW,
        lpDirectoryName,
        lpFreeBytesAvailableToCaller,
        lpTotalNumberOfBytes,
        lpTotalNumberOfFreeBytes);

    ADD_OUT_PARAM(PULARGE_INTEGER, lpFreeBytesAvailableToCaller);
    ADD_OUT_PARAM(PULARGE_INTEGER, lpTotalNumberOfBytes);
    ADD_OUT_PARAM(PULARGE_INTEGER, lpTotalNumberOfFreeBytes);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()