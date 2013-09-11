#pragma once


DEFINE_API_CLASS_BEGIN(GetLogicalDrives)

static std::wstring GetString_ReturnValue(UINT v)
{
    std::wostringstream oss;

    oss << hexf << v;

    if(v)
    {
        bool notFirst = false;
        oss << '[';
        for(wchar_t a = 'A'; a <= 'Z'; ++a)
        {
            if(v & (1 << (a - 'A')))
            {
                if(notFirst)
                {
                    oss << L", ";
                }
                else
                {
                    notFirst = true;
                }
                oss << a;
            }
        }
        oss << ']';
    }

    return oss.str();
}

DWORD operator()()
{
    API_CALL_C(DWORD, GetLogicalDrives);

    API_RETURN_C();
}

DEFINE_API_CLASS_END()