#pragma once


DEFINE_API_CLASS_BEGIN(CancelIoEx)

static std::wstring GetString_lpOverlapped(LPOVERLAPPED /*lpOverlapped*/)
{
    return L"";
}

BOOL operator()(
    __in      HANDLE hFile,
    __in_opt  LPOVERLAPPED lpOverlapped)
{
    ADD_IN_PARAM(HANDLE, hFile);
    ADD_IN_PARAM(_lpOverlapped, lpOverlapped);

    API_CALL_T(BOOL, CancelIoEx,
        hFile,
        lpOverlapped);

    API_RETURN_T();
}

DEFINE_API_CLASS_END()