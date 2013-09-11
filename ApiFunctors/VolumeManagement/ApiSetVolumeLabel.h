#pragma once


DEFINE_API_CLASS_BEGIN(SetVolumeLabel)

BOOL operator()(
    __in_opt LPCWSTR lpRootPathName,
    __in_opt LPCWSTR lpVolumeName)
{
    ADD_IN_PARAM(PSTR, lpRootPathName);
    ADD_IN_PARAM(PSTR, lpVolumeName);

    API_CALL_T(BOOL, SetVolumeLabelW,
        lpRootPathName,
        lpVolumeName);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()