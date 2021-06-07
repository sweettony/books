#include <iostream>
#include <utility>

int test()
{
    int a;
    int&& b = std::move(a);
    int& c = b;
    std::cout << &b <<" " << &a << " " << &c << std::endl;
    return 0;
}
struct cc
{
    int a;
    int b;
};
struct cc create_cc()
{
    struct cc tmp;
    return tmp;
}
//forwarding reference
template <typename T> int func(T&& c)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}
//lvalue reference
template <typename T> int func1(T& c)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}

int main()
{
    func(3);
    int a = 3;
    func(a);
    int&& b = std::move(a);
    int&& c = std::move(b);
    return 0;
}