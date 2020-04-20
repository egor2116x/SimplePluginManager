#pragma once
#include "Common.h"
#include "IPlugin.h"

class IPluginManager
{
public:
    IPluginManager();
    bool LoadPlugins(const std::wstring& folderPath = L"");
    bool InitPlugins();
    bool RunPlugins();
    bool FreePlugins();
    virtual unsigned GetVersion() = 0;
    virtual ~IPluginManager() {}
private:
    bool LoadPlugin(const std::wstring& filePath, std::unique_ptr<IPlugin>& plugin);
protected:
    unsigned m_Version;
private:
    std::vector<std::unique_ptr<IPlugin>> m_Plugins;
    std::vector<std::unique_ptr<IPlugin>> m_FailedPlugins;
};

class PluginManager_v1 : public IPluginManager
{
public:
    PluginManager_v1();
    virtual unsigned GetVersion() override;
private:
    
};
