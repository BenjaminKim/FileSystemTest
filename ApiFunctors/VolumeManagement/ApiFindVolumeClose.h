#pragma once


DEFINE_API_CLASS_BEGIN(FindVolumeClose)

BOOL operator()(
    __in HANDLE hFindVolume)
{
    ADD_IN_PARAM(HANDLE, hFindVolume);

    API_CALL_T(BOOL, FindVolumeClose,
        hFindVolume);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()