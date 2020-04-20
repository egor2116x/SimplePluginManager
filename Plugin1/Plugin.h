#include <string>
#define EXPORT_API extern "C" __declspec(dllexport)

#define VERSION 0x0001
#define NAME    L"Plugin 1"

class IPlugin
{
public:
    virtual unsigned GetVersion() = 0;
    virtual const wchar_t* GetName() = 0;
    virtual bool Init() = 0;
    virtual bool Run() = 0;
    virtual bool Release() = 0;
};

class Plugin : public IPlugin
{
public:
    Plugin() : m_Version(VERSION), m_Name(NAME) {}
    virtual unsigned GetVersion() override;
    virtual const wchar_t* GetName() override;
    virtual bool Init() override;
    virtual bool Run() override;
    virtual bool Release() override;
private:
    unsigned m_Version;
    std::wstring m_Name;
};

EXPORT_API IPlugin* GetPlugin();

