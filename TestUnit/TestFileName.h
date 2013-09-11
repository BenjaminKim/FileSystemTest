#pragma once

class TestFileName
{
public:
    TestFileName();
    std::wstring GetFirstFileName();
    std::wstring GetNextFileName();

protected:
    std::wstring IntegerToString(INT32 i);

private:
    size_t count_;
    std::wstring filename_;
    std::vector<std::wstring> extlist_;
    std::vector<std::wstring>::const_iterator extListIterator_;
};