#pragma once
#include "IMyInterface.h"

class ClassA : public IMyInterface
{
    virtual std::string f();
};