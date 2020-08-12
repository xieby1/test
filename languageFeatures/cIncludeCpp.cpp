#include "cIncludeCpp.h"
#include <iostream>

class C
{
public:
    std::string s;
    C() {s = "This is a class";}
};

extern "C"  void printClass()
{
    C c;
    std::cout << c.s << std::endl;
    return;
}
