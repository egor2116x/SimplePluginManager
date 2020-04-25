#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <Windows.h>

class IPlugin;
using GetPluginFunc = IPlugin * (*)();          // GetPlugin
extern const char* GET_PLUGIN;

inline void PrintConsole(std::wostream& out, const std::wstring& mess)
{
    out << mess << std::endl;
}

inline std::wstring GetExecAppPath()
{
    HMODULE hModule = GetModuleHandleW(NULL);
    std::vector<wchar_t> fullPathExe(MAX_PATH);
    DWORD result = 0;
    if (hModule != NULL)
    {
        while (true)
        {
            result = GetModuleFileNameW(hModule,
                reinterpret_cast<LPWSTR>(&fullPathExe[0]),
                fullPathExe.size());

            if (result == 0)
            {
                return std::move(std::wstring());
            }
            else if (fullPathExe.size() == result)
            {
                fullPathExe.resize(fullPathExe.size() * 2);
            }
            else
            {
                break;
            }
        }
    }

    std::wstring out;
    out.resize(fullPathExe.size());
    std::memcpy(&out[0], &fullPathExe[0], result * sizeof(wchar_t));
    std::string::size_type i = out.find_last_of(L"\\/");
    if (std::string::npos != i) out.erase(i);

    return out;
}


