#include <iostream>
#include <typeinfo>

class A
{
    public:
    A()
    {}
    ~A()
    {}
    int a;
};
class C
{
    public:
    C()
    {}
    ~C()
    {}
    int a;
};
class B : public A, public C
{
public:
    explicit B()
    {}
    ~B()
    {}
};
int main()
{
    B b;
    A* a = new B();
    std::cout << "a = " << a << std::endl;
    B* b = (B*)a;
    std::cout << "b = " << b << std::endl;
    C* c = (C*)b;
    std::cout << "c = " << c << std::endl;
}