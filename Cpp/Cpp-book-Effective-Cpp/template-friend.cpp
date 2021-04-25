#include <iostream>
#include <stdio.h>

template<typename T> class A;
template<typename T> A<T> doMultiply(const A<T>& lhs, const A<T>& rhs);

template<class T>
class A
{
   public:
     A(T a = 0): m_a(a) {}

    void print()
    {
        std::cout << "i am here" << std::endl;
    }

    friend A operator*(const A& l, const A& r)
    {
        return doMultiply<T>(l, r);
    }
   private:
     T m_a;
};
//注意：template函数参数不进行隐式的转换
template<typename T> A<T> doMultiply(const A<T>& lhs, const A<T>& rhs)
{
    std::cout << "i am in" << __PRETTY_FUNCTION__ <<std::endl;
}

int main()
{
    A<int> a;
    int b;
    a * b;
  return 0;
}