#include "stdafx.h"
#include "TestLog.h"
#include <iostream>
#include <iomanip>

size_t TestLog::caseN_ = 0;
size_t TestLog::specificCase_ = 0;
SYSTEMTIME TestLog::starttime_ = { 0 };
SYSTEMTIME TestLog::endtime_ = { 0 };
bool TestLog::fUseTimer_ = false;
bool TestLog::minimalOutput_ = false;

TestLog::TestLog(std::wostream& output, const std::wstring& testName)
    : output_(output)
    , testName_(testName)
    , success_(false)
{
    if (TestLog::minimalOutput_ == false)
    {
        output_ << L"(Case" << caseN_ << L")[" << testName_ << L"]: Start." << std::endl;
    } 
}

TestLog::~TestLog()
{
    if (TestLog::minimalOutput_ == false)
    {
        output_ << L"(Case" << caseN_ << L")[" << testName_ << L"]: End. " <<
            ((success_) ? L"Success" : L"Fail") << std::endl << std::endl;
    }
    else
    {
        output_ << L"(Case " << std::setfill(L'0') << std::setw(5) << caseN_ << L") " << ((success_) ? L"OK" : L"KO") << L" [" << testName_ << L"]" << std::endl;
    }
}

std::wostream& TestLog::GetStream(MessageType msgType)
{
    if (TestLog::minimalOutput_ == true)
    {
        return std::wcerr;
    }
    switch(msgType)
    {
    case MT_NONE:
        break;

    case MT_MESSAGE:
        output_ << L"(MESSAGE) ";
        break;

    case MT_WARNING:
        output_ << L"(WARNING) ";
        break;

    case MT_ERROR:
        output_ << L"(ERROR) ";
        break;
    }

    return output_;
}

size_t TestLog::CaseN()
{
    return caseN_;
}

void TestLog::Ok()
{
    success_ = true;
}

bool TestLog::IsSkip()
{
    ++caseN_;

    if(specificCase_)
    {
        return (specificCase_ != caseN_);
    }

    return false;
}

void TestLog::SetSpecificCase(size_t i)
{
    specificCase_ = i;
}

void TestLog::SetRunningTime(const SYSTEMTIME& s, const SYSTEMTIME& e)
{
    starttime_ = s;
    endtime_ = e;
}