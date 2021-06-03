#include <iostream>
#include <stdio.h>

template<typename T> class A;

template<typename T> A<T> operator* (const A<T>& l, const A<T>& r);

template<class T>
class A
{
  public:
    A(T a = 0): m_a(a) {}

  void print()
  {
      std::cout << "i am here" << std::endl;
  }
  friend A<T> operator*<T> (const A<T>& l, const A<T>& r);
private:
  T m_a;
};

template<typename T> A<T> operator*(const A<T>& l, const A<T>& r)
{
    std::cout << "i am in " << __PRETTY_FUNCTION__ <<std::endl;
}

int main()
{
  A<int> a;
  //A<int> b;
  int b;
  a * b;
  return 0;
}