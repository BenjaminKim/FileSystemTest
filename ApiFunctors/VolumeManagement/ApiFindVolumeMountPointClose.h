#pragma once


DEFINE_API_CLASS_BEGIN(FindVolumeMountPointClose)

BOOL operator()(
    __in HANDLE hFindVolumeMountPoint)
{
    ADD_IN_PARAM(HANDLE, hFindVolumeMountPoint);

    API_CALL_T(BOOL, FindVolumeMountPointClose,
        hFindVolumeMountPoint);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()