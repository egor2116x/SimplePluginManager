#include "pch.h"
#include "framework.h"
#include "Plugin.h"
#include <iostream>

unsigned Plugin::GetVersion()
{
    return m_Version;
}

const wchar_t* Plugin::GetName()
{
    return m_Name.c_str();
}

bool Plugin::Init()
{
    std::wcout << L"Plugin " << m_Name << L" init data" << std::endl;
    return true;
}

bool Plugin::Run()
{
    std::wcout << L"Plugin " << m_Name << L" Run" << std::endl;
    return true;
}

bool Plugin::Release()
{
    std::wcout << L"Plugin " << m_Name << L" Release data" << std::endl;
    return true;
}

unsigned GetPluginVersion()
{
    return VERSION;
}

const wchar_t* GetPluginName()
{
    return NAME;
}

IPlugin* GetPlugin()
{
    return new Plugin();
}
