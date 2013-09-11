#include "stdafx.h"
#include "TestFileName.h"

TestFileName::TestFileName()
: filename_(L"GeneratedByWidTestUnit()#~!&="),
count_(0)
{
    extlist_.push_back(L"exe"); extlist_.push_back(L"alz"); extlist_.push_back(L"7z"); extlist_.push_back(L"bat");
    extlist_.push_back(L"vod"); extlist_.push_back(L"txt"); extlist_.push_back(L"vim"); extlist_.push_back(L"rar");
    extlist_.push_back(L"aspx"); extlist_.push_back(L"conf"); extlist_.push_back(L"xls"); extlist_.push_back(L"hwp");
}

std::wstring TestFileName::GetFirstFileName()
{
    extListIterator_ = extlist_.begin();
    return filename_ + IntegerToString(count_++) + L"." + *extListIterator_++;
}

std::wstring TestFileName::GetNextFileName()
{
    if(extListIterator_ == extlist_.end())
    {
        extListIterator_ = extlist_.begin();
    }

    return filename_ + IntegerToString(count_++) + L"." + *extListIterator_++;
}

std::wstring TestFileName::IntegerToString(INT32 i)
{
    std::wostringstream oss;
    oss << i;
    return oss.str();
}
