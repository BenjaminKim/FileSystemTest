#pragma once


class Timer
{
public:
    Timer();
    double GetElapsedTime();
    LONGLONG GetElapsedTime(LONGLONG resolutionPerSecond);
    static std::wstring GetCurrentDateTime();

private:
    double GetFrequency();
    LARGE_INTEGER start_;
};