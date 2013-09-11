#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif


#include <Windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <functional>

#include "ApiStatistics.h"
#include "Timer.h"
#include "ApiFunctors/ApiFunction.h"
#include "TestUnit/TestLog.h"
#include "TestUnit/TestUtility.h"
#include "ApiFunctors/FileManagement/ApiDeleteFile.h"
#include <assert.h>

/* 
When the compiler sees a line like this:
chMSG(Fix this later);

it outputs a line like this:

c:\CD\CmnHdr.h(82):Fix this later

You can easily jump directly to this line and examine the surrounding code.
*/

#define chSTR2(x) #x
#define chSTR(x)  chSTR2(x)

#define chMSG(desc) message(__FILE__ "(" chSTR(__LINE__) "): --------" #desc "--------")
#define chFixLater message(__FILE__ "(" chSTR(__LINE__) "): --------Fix this later--------")

#define FixLater \
    do { \
    __pragma(chFixLater) \
    __pragma (warning(push)) \
    __pragma (warning(disable:4127)) \
    } while(0) \
    __pragma (warning(pop))

#define MSG(desc) \
    do { \
    __pragma(chMSG(desc)) \
    __pragma (warning(push)) \
    __pragma (warning(disable:4127)) \
    } while(0) \
    __pragma (warning(pop))


///////////////////////////// chBEGINTHREADEX Macro ///////////////////////////


// This macro function calls the C runtime's _beginthreadex function. 
// The C runtime library doesn't want to have any reliance on Windows' data 
// types such as HANDLE. This means that a Windows programmer needs to cast
// values when using _beginthreadex. Since this is terribly inconvenient, 
// I created this macro to perform the casting.
typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define chBEGINTHREADEX(psa, cbStackSize, pfnStartAddr, \
    pvParam, dwCreateFlags, pdwThreadId)                 \
    ((HANDLE)_beginthreadex(                          \
    (void *)        (psa),                         \
    (unsigned)      (cbStackSize),                 \
    (PTHREAD_START) (pfnStartAddr),                \
    (void *)        (pvParam),                     \
    (unsigned)      (dwCreateFlags),               \
    (unsigned *)    (pdwThreadId)))