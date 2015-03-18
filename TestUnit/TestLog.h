#pragma once

class TestLog
{
public:
    TestLog(std::wostream& output, const std::wstring& testName);
    ~TestLog();

    enum MessageType
    {
        MT_NONE,
        MT_MESSAGE,
        MT_WARNING,
        MT_ERROR,
    };

    std::wostream& GetStream(MessageType msgType);
    void Ok();
    static size_t CaseN();
    static bool IsSkip();
    static void SetSpecificCase(size_t i);
    static void SetRunningTime(const SYSTEMTIME& s, const SYSTEMTIME& e);
    
protected:
    /// workaround compiler warning.
    TestLog& operator=(const TestLog&);

private:
    std::wostream& output_;
    std::wstring testName_;
    bool success_;
    static size_t caseN_;
    static size_t specificCase_;
public:
    static SYSTEMTIME starttime_;
    static SYSTEMTIME endtime_;
    static bool fUseTimer_;
};

#define DEF_TESTLOG_T(x) if(TestLog::IsSkip()) { return; } TestLog log(wcout, _T(x))