#pragma once

#include "../Combinator.h"

void Test_MoveFileEx_Basic(DWORD dwFlags);
void Test_MoveFileEx_NoExistingSrc(DWORD dwFlags);
void Test_MoveFileEx_SharingViolationSrcShareMode(DWORD dwShareMode, DWORD dwFlags);
void Test_MoveFileEx_SharingViolationSrc(DWORD dwFlags);
void Test_MoveFileEx_ExistingDst(DWORD dwFlags);
void Test_MoveFileEx_ExistingDstSharingViolationShareMode(DWORD dwShareMode, DWORD dwFlags);
void Test_MoveFileEx_ExistingDstSharingViolation(DWORD dwFlags);

inline void Test_MoveFileEx_All()
{
    BitCombinator<DWORD> c;
    c.AddAllSingleBit(
        MOVEFILE_COPY_ALLOWED |
        //MOVEFILE_CREATE_HARDLINK | This is just reserved flag.
        MOVEFILE_REPLACE_EXISTING |
        MOVEFILE_WRITE_THROUGH |
        0);

    DWORD dwFlags = 0;
    while((dwFlags = c.Next(dwFlags)) != 0)
    {
        Test_MoveFileEx_Basic(dwFlags);
    }
    Test_MoveFileEx_Basic(0);

    while((dwFlags = c.Next(dwFlags)) != 0)
    {
        Test_MoveFileEx_NoExistingSrc(dwFlags);
    }
    Test_MoveFileEx_NoExistingSrc(0);

    while((dwFlags = c.Next(dwFlags)) != 0)
    {
        Test_MoveFileEx_SharingViolationSrc(dwFlags);
    }
    Test_MoveFileEx_SharingViolationSrc(0);

    while((dwFlags = c.Next(dwFlags)) != 0)
    {
        Test_MoveFileEx_ExistingDst(dwFlags);
    }
    Test_MoveFileEx_ExistingDst(0);

    while((dwFlags = c.Next(dwFlags)) != 0)
    {
        Test_MoveFileEx_ExistingDstSharingViolation(dwFlags);
    }
    Test_MoveFileEx_ExistingDstSharingViolation(0);
}