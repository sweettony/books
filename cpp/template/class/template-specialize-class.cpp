#include "template-specialize-class.h"

void Demo<int>::print()
{
    std::cout << "print in Demo<int> header" << std::endl;
}
