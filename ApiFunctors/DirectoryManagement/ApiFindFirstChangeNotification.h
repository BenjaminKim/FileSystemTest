#pragma once


DEFINE_API_CLASS_BEGIN(FindFirstChangeNotification)

HANDLE  operator()(
    __in  LPCTSTR lpPathName,
    __in  BOOL bWatchSubtree,
    __in  DWORD dwNotifyFilter)
{
    ADD_IN_PARAM(PSTR, lpPathName);
    ADD_IN_PARAM(BOOL, bWatchSubtree);
    ADD_IN_PARAM(DWORD, dwNotifyFilter);

    API_CALL_T(HANDLE, FindFirstChangeNotificationW,
        lpPathName,
        bWatchSubtree,
        dwNotifyFilter);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()