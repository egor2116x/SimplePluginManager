#include "pch.h"
#include "framework.h"
#include "PluginManager.h"

const char* GET_PLUGIN = "GetPlugin";

IPluginManager::IPluginManager()
{
    m_Version = 0x0000;
}

PluginManager_v1::PluginManager_v1()
{
    m_Version = 0x0001;
}

unsigned PluginManager_v1::GetVersion()
{
    return m_Version;
}

bool IPluginManager::LoadPlugins(const std::wstring& folderPath)
{
    PrintConsole(std::wcout, L"[Plugin manager] LoadPlugins start");
    std::wstring searchPath = folderPath + L"*.dll";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        PrintConsole(std::wcout, L"[Plugin manager] Error when getting first plugin file = " + searchPath);
        return false;
    }

    do
    {
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            std::unique_ptr<IPlugin> plugin;
            if (!LoadPlugin(folderPath + fd.cFileName, plugin))
            {
                continue;
            }
            PrintConsole(std::wcout, std::wstring(L"[Plugin manager] Plugin was loaded = ") + fd.cFileName);
            m_Plugins.emplace_back(std::move(plugin));
        }
    } while (::FindNextFile(hFind, &fd));

    ::FindClose(hFind);
    PrintConsole(std::wcout, L"[Plugin manager] LoadPlugins end");
    return true;
}

bool IPluginManager::InitPlugins()
{
    PrintConsole(std::wcout, L"[Plugin manager] Init plugins start");
    if (m_Plugins.empty())
    {
        PrintConsole(std::wcout, L"[Plugin manager] Has no any plugins");
        return false;
    }
    for (auto plugin = m_Plugins.begin(); plugin != m_Plugins.end(); plugin++)
    {
        if (!(*plugin)->Init())
        {
            IPlugin* p = plugin->release();
            m_Plugins.erase(plugin);
            m_FailedPlugins.emplace_back(std::move(std::unique_ptr<IPlugin>(p)));
        }
    }

    for (auto plugin = m_FailedPlugins.begin(); plugin != m_FailedPlugins.end(); plugin++)
    {
        PrintConsole(std::wcout, std::wstring(L"[Plugin manager] Plugin initialyze failed, name") + (*plugin)->GetName());
    }

    PrintConsole(std::wcout, L"[Plugin manager] Init plugins end");
    return true;
}

bool IPluginManager::RunPlugins()
{
    PrintConsole(std::wcout, L"[Plugin manager] Run start");
    if (m_Plugins.empty())
    {
        PrintConsole(std::wcout, L"[Plugin manager] Has no any valid plugins");
        return false;
    }
    for (auto plugin = m_Plugins.begin(); plugin != m_Plugins.end(); plugin++)
    {
        if (!(*plugin)->Run())
        {
            IPlugin* p = plugin->release();
            m_Plugins.erase(plugin);
            m_FailedPlugins.emplace_back(std::move(std::unique_ptr<IPlugin>(p)));
        }
    }

    PrintConsole(std::wcout, L"[Plugin manager] Run end");
    return true;
}

bool IPluginManager::FreePlugins()
{
    m_Plugins.clear();
    m_FailedPlugins.clear();
    PrintConsole(std::wcout, L"[Plugin manager] Free all plugins end");
    return true;

}

bool IPluginManager::LoadPlugin(const std::wstring& filePath, std::unique_ptr<IPlugin>& plugin)
{
    HMODULE lib = ::LoadLibraryW(filePath.c_str());
    if (lib == nullptr)
    {
        PrintConsole(std::wcout, std::wstring(L"[Plugin manager] Error when load plugin name = ") + filePath);
        return false;
    }

    GetPluginFunc GetPluginFunc = nullptr;
    reinterpret_cast<FARPROC&>(GetPluginFunc) = ::GetProcAddress(lib, GET_PLUGIN);
    if (GetPluginFunc == nullptr)
    {
        PrintConsole(std::wcout, L"[Plugin manager] Error when GetPluginFunc = " + filePath);
        FreeLibrary(lib);
        return false;
    }

    IPlugin* plg = GetPluginFunc();
    if (plg == nullptr)
    {
        PrintConsole(std::wcout, L"[Plugin manager] Error when load plugin instance = " + filePath);
        FreeLibrary(lib);
        return false;
    }

    plugin.reset(plg);

    return true;
}
