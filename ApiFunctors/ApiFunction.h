#pragma once

std::wstring GetStringPSTR(LPCWSTR p);
std::wstring GetStringPPSTR(const wchar_t * const * pp);
//std::wstring GetStringLPFILETIME(LPFILETIME ft);
std::wstring GetStringHANDLE(HANDLE h);
std::wstring GetStringHandleValue(HANDLE h);
std::wstring GetStringPVOID(const void* p);
std::wstring GetStringPointerValue(const void* p);
std::wstring GetStringBOOL(BOOL v);
std::wstring GetStringPBOOL(const BOOL* p);
std::wstring GetStringINT32(int v);
std::wstring GetStringUINT32(unsigned int v);
std::wstring GetStringLONG(long v);
std::wstring GetStringULONG(unsigned long v);
std::wstring GetStringULONG_PTR(ULONG_PTR v);
std::wstring GetStringDWORD(DWORD v);
std::wstring GetStringPINT32(const int* p);
std::wstring GetStringPUINT32(const unsigned int* p);
std::wstring GetStringPLONG(const long* p);
std::wstring GetStringPULONG(const unsigned long* p);
std::wstring GetStringPDWORD(const DWORD* p);
std::wstring GetStringLARGE_INTEGER(LARGE_INTEGER li);
std::wstring GetStringPLARGE_INTEGER(const LARGE_INTEGER* pLi);
std::wstring GetStringULARGE_INTEGER(ULARGE_INTEGER lu);
std::wstring GetStringPULARGE_INTEGER(const ULARGE_INTEGER* pLu);
std::wstring GetStringINT64(INT64 v);
std::wstring GetStringPINT64(const INT64* p);
std::wstring GetString_dwFileAttributes(DWORD dwFileAttributes);
std::wstring GetString_FileTime(__in const FILETIME* pFileTime);
std::wstring GetErrorDefineString(DWORD error);

class ApiFunction;
std::wostream& operator<<(std::wostream& output, const ApiFunction& a);

class ApiFunction
{
public:
    ApiFunction(std::wostream& out = std::wcout) : output_(out), 
        enableLog_(true),
        printDuration_(false),
        printDateTime_(false),
        elapsedtime_(0)
    {
    }

    void SetFunctionName(PCWSTR pFunctionName);
    void AddInParam(PCWSTR pName, const std::wstring& value);
    void AddOutParam(PCWSTR pName, const std::wstring& value);
    void SetReturnValue(const std::wstring& returnValue);
    void SetLastError();
    virtual void Output(std::wostream& output) const;
    void OutputFlush();
    void ResetStatistics();
    void PrintStatistics() const;
    void EnableLog(bool fEnable);
    void EnableDurationOutput(bool fEnable);
    void EnableDateTimeOutput(bool fEnable);

protected:
    ///컴파일러 경고 메세지 회피.
    ///할당 연산자가 필요해질 때 구현 하도록 한다.
    ApiFunction& operator=(const ApiFunction&) {}
    void SetElapsedTime(const double& elapsedTime) { elapsedtime_ = elapsedTime; }
    ApiStatistics statistics_;
    
#define DECLARE_GET_STRING(Type, Typedef) std::wstring GetString##Type(Typedef v){ return ::GetString##Type(v); }
    DECLARE_GET_STRING(PSTR, LPCWSTR)
    DECLARE_GET_STRING(PPSTR, const wchar_t * const *)
    DECLARE_GET_STRING(HANDLE, HANDLE)
    DECLARE_GET_STRING(HandleValue, HANDLE)
    DECLARE_GET_STRING(PVOID, const void*)
    DECLARE_GET_STRING(PointerValue, const void*)
    DECLARE_GET_STRING(BOOL, BOOL)
    DECLARE_GET_STRING(PBOOL, const BOOL*)
    DECLARE_GET_STRING(INT32, int)
    DECLARE_GET_STRING(PINT32, const int*)
    DECLARE_GET_STRING(UINT32, unsigned int)
    DECLARE_GET_STRING(PUINT32, const unsigned int*)
    DECLARE_GET_STRING(LONG, long)
    DECLARE_GET_STRING(PLONG, const long*)
    DECLARE_GET_STRING(ULONG, unsigned long)
    DECLARE_GET_STRING(PULONG, const unsigned long*)
    DECLARE_GET_STRING(ULONG_PTR, ULONG_PTR)
    DECLARE_GET_STRING(DWORD, DWORD)
    DECLARE_GET_STRING(PDWORD, const DWORD*)
    DECLARE_GET_STRING(INT64, INT64)
    DECLARE_GET_STRING(PINT64, const INT64*)
    DECLARE_GET_STRING(LARGE_INTEGER, LARGE_INTEGER)
    DECLARE_GET_STRING(PLARGE_INTEGER, const LARGE_INTEGER*)
    DECLARE_GET_STRING(ULARGE_INTEGER, ULARGE_INTEGER)
    DECLARE_GET_STRING(PULARGE_INTEGER, const ULARGE_INTEGER*)

private:
    typedef std::pair<std::wstring, std::wstring> param;
    std::wstring apiFunctionName_;
    std::vector<std::pair<std::wstring, std::wstring>> argInList_;
    std::vector<std::pair<std::wstring, std::wstring>> argOutList_;
    std::wstring returnValue_;
    std::wstring lastError_;
    std::wostream& output_;
    double elapsedtime_;
    bool enableLog_;
    bool printDuration_;
    bool printDateTime_;
    static size_t caseN_;

    std::wstring GetErrorDefineString(DWORD error) { return ::GetErrorDefineString(error); }
};

inline std::wostream& __CLRCALL_OR_CDECL hexf(std::wostream& wos)
{
    return wos << L"0x" << std::setfill(static_cast<wchar_t>('0')) << std::setw(8) << std::hex << std::uppercase;
}

//#define DEF_OSS() std::wostringstream oss
//#define RET_OSS() return oss.str()

#define CHECK_BIT_BEGIN(Var)\
    UINT64 x = (UINT64)(Var);\
    std::wostringstream oss; oss << (Var);\
    if(x)\
    {\
        bool notFirst = false;\
        oss << '[';

#define CHECK_BIT_BEGIN_HEX(Var)\
    UINT64 x = (UINT64)(Var);\
    std::wostringstream oss; oss << hexf << (Var);\
    if(x)\
    {\
        bool notFirst = false;\
        oss << '[';

#define CHECK_BIT_END()\
        oss << ']';\
    }\
    return oss.str();

#define CHECK_BIT(Flag)\
    if((x & (Flag)) == (Flag))\
    {\
        if(notFirst)\
        {\
            oss << L", ";\
        }\
        else\
        {\
            notFirst = true;\
        }\
        oss << L#Flag;\
    }

#define CHECK_BIT_CLEAR(Flag)\
    if((x & (Flag)) == (Flag))\
    {\
        if(notFirst)\
        {\
            oss << L", ";\
        }\
        else\
        {\
            notFirst = true;\
        }\
        oss << L#Flag;\
        x &= ~((UINT64)Flag);\
    }

#define SWITCH_BEGIN(Var) std::wostringstream oss; oss << (Var); switch(Var) {
#define SWITCH_BEGIN_HEX(Var) std::wostringstream oss; oss << hexf << (Var); switch(Var) {
#define CASE(Name) case Name: oss << (L"(" L#Name L")"); return oss.str();
#define SWITCH_END() default: return L"unknown"; }

#define DEFINE_API_CLASS_BEGIN(ApiName)\
    class Api##ApiName;\
    extern Api##ApiName api##ApiName;\
    extern Api##ApiName u##ApiName;\
    class Api##ApiName : public ApiFunction\
    {\
    public:\
        Api##ApiName() { SetFunctionName(L#ApiName); }

#define DEFINE_API_CLASS_DYN_BEGIN(ApiName, LibName)\
    template<typename FuncType>\
    class Api##ApiName##T : public ApiFunction\
    {\
    private:\
        HMODULE hModule_;\
        FuncType pFunc_;\
        LPWSTR pLibName_;\
    public:\
        Api##ApiName##T(): hModule_(0), pFunc_(0), pLibName_(L#LibName) { SetFunctionName(L#ApiName); }\
        ~Api##ApiName##T(){ if(hModule_){ FreeLibrary(hModule_); } }

#define DEFINE_API_CLASS_END() };

#define DEFINE_API_CLASS_DYN_END(ApiName, ApiType) };\
    typedef Api##ApiName##T<ApiType> Api##ApiName;\
    extern Api##ApiName api##ApiName;\
    extern Api##ApiName u##ApiName;

#define ADD_IN_PARAM(TypeName, Var, ...) AddInParam(L#Var, GetString##TypeName(Var, __VA_ARGS__))
#define ADD_OUT_PARAM(TypeName, Var, ...) AddOutParam(L#Var, GetString##TypeName(Var, __VA_ARGS__))

#define API_CALL_T(Type, ApiName, ...)\
    Timer t;\
    ::SetLastError(ERROR_SUCCESS); Type returnValueT = ApiName(__VA_ARGS__); SetLastError();\
    double d = t.GetElapsedTime();\
    SetElapsedTime(d);\
    statistics_.InsertData(d);\
    SetReturnValue(GetString##Type(returnValueT))

#define API_DYN_CALL_T(Type, ApiName, ...)\
    if(!hModule_)\
    {\
        hModule_ = LoadLibraryW(pLibName_);\
        if(!hModule_){ return Type(0); }\
    }\
    if(!pFunc_)\
    {\
        pFunc_ = (FuncType)GetProcAddress(hModule_, #ApiName);\
        if(!pFunc_){ return Type(0); }\
    }\
    Timer t;\
    ::SetLastError(ERROR_SUCCESS); Type returnValueT = (*pFunc_)(__VA_ARGS__); SetLastError();\
    double d = t.GetElapsedTime();\
    SetElapsedTime(d);\
    statistics_.InsertData(d);\
    SetReturnValue(GetString##Type(returnValueT))

#define API_RETURN_T()\
    OutputFlush();\
    return returnValueT

#define API_CALL_C(Type, ApiName, ...)\
    Timer t;\
    ::SetLastError(ERROR_SUCCESS); Type returnValueC = ApiName(__VA_ARGS__); SetLastError();\
    double d = t.GetElapsedTime();\
    SetElapsedTime(d);\
    statistics_.InsertData(d);\
    SetReturnValue(GetString_ReturnValue(returnValueC))

#define API_RETURN_C()\
    OutputFlush();\
    return returnValueC

#define API_CALL_V(ApiName, ...)\
    Timer t;\
    ::SetLastError(ERROR_SUCCESS); ApiName(__VA_ARGS__); SetLastError();\
    double d = t.GetElapsedTime();\
    SetElapsedTime(d);\
    statistics_.InsertData(d);\
    SetReturnValue(L"(VOID)")

#define API_RETURN_V()\
    OutputFlush();\
    return
