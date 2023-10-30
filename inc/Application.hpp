#pragma once

class Application
{
public:
    virtual ~Application() { }
    virtual void run() = 0;
protected:
    Application() { }
};
