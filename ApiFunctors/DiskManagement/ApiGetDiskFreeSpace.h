#pragma once


DEFINE_API_CLASS_BEGIN(GetDiskFreeSpace)

BOOL operator()(
    __in_opt  LPCWSTR lpRootPathName,
    __out_opt LPDWORD lpSectorsPerCluster,
    __out_opt LPDWORD lpBytesPerSector,
    __out_opt LPDWORD lpNumberOfFreeClusters,
    __out_opt LPDWORD lpTotalNumberOfClusters)
{
    ADD_IN_PARAM(PSTR, lpRootPathName);

    API_CALL_T(BOOL, GetDiskFreeSpaceW,
        lpRootPathName,
        lpSectorsPerCluster,
        lpBytesPerSector,
        lpNumberOfFreeClusters,
        lpTotalNumberOfClusters);

    ADD_OUT_PARAM(PDWORD, lpSectorsPerCluster);
    ADD_OUT_PARAM(PDWORD, lpBytesPerSector);
    ADD_OUT_PARAM(PDWORD, lpNumberOfFreeClusters);
    ADD_OUT_PARAM(PDWORD, lpTotalNumberOfClusters);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()