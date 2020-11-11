#include <iostream>
#include "ClassA.h"
#include "ClassB.h"

using namespace std;

int main()
{
    ClassA classA;
    ClassB classB;

    cout << classB.g(classA).c_str() << endl;

    return 0;
}
