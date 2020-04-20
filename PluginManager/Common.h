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


