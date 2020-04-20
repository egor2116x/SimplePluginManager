#pragma once

class IPlugin
{
public:
    virtual unsigned GetVersion() = 0;
    virtual const wchar_t* GetName() = 0;
    virtual bool Init() = 0;
    virtual bool Run() = 0;
    virtual bool Release() = 0;
};
