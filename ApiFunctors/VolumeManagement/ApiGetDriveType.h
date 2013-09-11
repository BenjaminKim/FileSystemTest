#pragma once


DEFINE_API_CLASS_BEGIN(GetDriveType)

static std::wstring GetString_ReturnValue(UINT v)
{
    SWITCH_BEGIN(v)
        CASE(DRIVE_UNKNOWN)
        CASE(DRIVE_NO_ROOT_DIR)
        CASE(DRIVE_REMOVABLE)
        CASE(DRIVE_FIXED)
        CASE(DRIVE_REMOTE)
        CASE(DRIVE_CDROM)
        CASE(DRIVE_RAMDISK)
    SWITCH_END()
}

UINT operator()(
    __in_opt LPCWSTR lpRootPathName)
{
    ADD_IN_PARAM(PSTR, lpRootPathName);

    API_CALL_C(UINT, GetDriveTypeW,
        lpRootPathName);

    API_RETURN_C();
}

DEFINE_API_CLASS_END()