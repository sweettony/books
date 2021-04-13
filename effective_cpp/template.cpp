#include <iostream>
#include "template.h"

int func_no_temp(const int& val)
{
    std::cout << "i love you" << std::endl;
    return 0;
}
int main()
{
    func<int>(8);
    func_no_temp(9);
    return 0;
}