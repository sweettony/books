#include <iostream>
#include <vector>
#include "template.h"

int func_no_temp(const int& val)
{
    std::cout << "i love you" << std::endl;
    return 0;
}
ZZ g_z;

int main()
{
    //func<int>(8);
    //func_no_temp(9);
    //Myclass<ZZ, 3> cc;
    //Myclass<int, 1> cc1;
    std::vector<ZZ> v = std::vector<ZZ>(5);
    std::cout << "vector size = " << v.size() << "; " << "addr = " << &v[0] << "." << std::endl;
    //std::cout<< &cc.a << std::endl;
    return 0;
}