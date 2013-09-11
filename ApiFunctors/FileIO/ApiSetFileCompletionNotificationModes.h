#pragma once


DEFINE_API_CLASS_BEGIN(SetFileCompletionNotificationModes)

static std::wstring GetString_Flags(UCHAR Flags)
{
    CHECK_BIT_BEGIN_HEX(Flags)

    CHECK_BIT(FILE_SKIP_COMPLETION_PORT_ON_SUCCESS)
    CHECK_BIT(FILE_SKIP_SET_EVENT_ON_HANDLE)

    CHECK_BIT_END()
}

BOOL operator()(
    __in  HANDLE FileHandle,
    __in  UCHAR Flags)
{
    ADD_IN_PARAM(HANDLE, FileHandle);
    ADD_IN_PARAM(_Flags, Flags);

    API_CALL_T(BOOL, SetFileCompletionNotificationModes,
        FileHandle,
        Flags);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()