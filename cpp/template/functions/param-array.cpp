#include <iostream>

template<typename T>int func(T cc)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return 0;
}
template<typename T>int func1(T& cc)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return 0;
}
template<typename T>int func2(T* cc)
{
    std::cout << __PRETTY_FUNCTION__ << '\n';
    return 0;
}
int main()
{
    const int bb[3] = {1, 2, 3};
    func(bb);
    func1(bb);
    func2(bb);
    return 0;
}
