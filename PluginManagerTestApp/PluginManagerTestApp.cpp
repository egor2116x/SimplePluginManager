#include <iostream>
#include "PluginManager.h"


int main()
{
    PluginManager_v1 pluginManager;

    PrintConsole(std::wcout, std::wstring(L"Plugin manager version=") + std::to_wstring(pluginManager.GetVersion()));

    if (!pluginManager.LoadPlugins(L"C:\\Users\\Egor\\source\\repos\\PluginManager\\Debug\\"))
        return 1;

    if (!pluginManager.InitPlugins())
        return 1;

    if (!pluginManager.RunPlugins())
        return 1;

    if (!pluginManager.FreePlugins())
        return 1;

    std::wcout << L"Test application completed";
    std::wcin.get();
    return 0;
}

