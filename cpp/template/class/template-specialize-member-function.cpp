#include "template-specialize-member-function.h"

//need template<>
template<> void Demo<int>::print()
{
    std::cout << "print in Demo<int>" << std::endl;
}