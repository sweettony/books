#include <iostream>
class B
{
public:
    B(){}
    ~B(){}
public:
    int m_a;
};

class A
{
public:
    A(){}
    ~A(){}
    A(B b){ m_a = b.m_a; }
public:
    int m_a;
};

template<typename T> void max(T a, T b)
{
    return; //(a > b ? a : b);
}

int main()
{
    //max<int>(3, 0.9);
    max(3, 0);
    A a;
    B b;
    max<A>(a, b);
    return 0;
}