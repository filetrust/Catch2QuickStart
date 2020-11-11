#include "ClassB.h"

std::string ClassB::g(IMyInterface& myInterface)
{ 
    return myInterface.f(); 
}
