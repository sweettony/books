#include "specilize.h"

template<> void func<int>()
{
    std::cout << "in func<int>" << std::endl;
    return;
}
