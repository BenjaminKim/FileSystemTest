#include "stdafx.h"
#include "Timer.h"
#include <math.h>


Timer::Timer()
{
    DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
    ::QueryPerformanceCounter(&start_);
    ::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
}

double Timer::GetFrequency()
{
    LARGE_INTEGER proc_freq;

    if(!::QueryPerformanceFrequency(&proc_freq))
    {
        return 1.0;
    }

    return static_cast<double>(proc_freq.QuadPart ? proc_freq.QuadPart : 1.0);
}

double Timer::GetElapsedTime()
{
    LARGE_INTEGER stop;
    DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
    ::QueryPerformanceCounter(&stop);
    static double frequency = GetFrequency();
    ::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

    return static_cast<double>(stop.QuadPart - start_.QuadPart) / frequency;
}

LONGLONG Timer::GetElapsedTime(LONGLONG resolutionPerSecond)
{
    LARGE_INTEGER stop;
    DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), 0);
    ::QueryPerformanceCounter(&stop);
    static double frequency = GetFrequency();
    ::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

    return static_cast<LONGLONG>(0.5 + floor(0.5 + static_cast<double>(stop.QuadPart - start_.QuadPart) * resolutionPerSecond / frequency));
}

std::wstring Timer::GetCurrentDateTime()
{
    SYSTEMTIME systime;
    GetLocalTime(&systime);		
    TCHAR szLogHeader[60] = { 0 };

    _stprintf_s(szLogHeader, _countof( szLogHeader ), _T("[%02d:%02d:%02d.%03d] "),
        systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

    return std::wstring(szLogHeader);
}