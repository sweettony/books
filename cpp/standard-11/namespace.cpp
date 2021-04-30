#include <iostream>
namespace zz
{
    int func(double a)
    {
        std::cout << "zz" << std::endl;
    }
};

int func(int a)
{
    std::cout << "in global" << std::endl;
}

int func(double a)
{
    std::cout << "in global 2" << std::endl;
}
//using namespace zz;

int main()
{
    extern int func(double a);
    func(3);
    return 0;
}