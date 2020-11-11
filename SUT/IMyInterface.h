#pragma once
#include <iostream>

class IMyInterface
{
public:
    virtual ~IMyInterface() {};
    virtual std::string f() = 0;
};