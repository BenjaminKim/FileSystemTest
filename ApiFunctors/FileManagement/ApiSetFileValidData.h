#pragma once


DEFINE_API_CLASS_BEGIN(SetFileValidData)

BOOL operator()(
    __in  HANDLE hFile,
    __in  LONGLONG ValidDataLength)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(INT64, ValidDataLength);

    API_CALL_T(BOOL, SetFileValidData,
        hFile,
        ValidDataLength);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()