#ifndef TEMPLATE_H_
#define TEMPLATE_H_
#include <iostream>


template<typename T>int func(const T& val)
{
    std::cout << "i love you" << std::endl;
    return 0;
}
class ZZ
{
public:
    ZZ()
    {
        std::cout<< "you are my son" << std::endl; 
    }
    ~ZZ()
    {

    }
private:
    int m_a;
};

template<typename T, int size>
class Myclass
{
public:
    Myclass()
    {

    }
    ~Myclass()
    {

    }
    T* get()
    {
        return a;
    }
    T get0()
    {
        return a[0];
    }
    
    static T a[size];
    static ZZ b;
};

template<typename T, int size> T Myclass<T, size>::a[size] = {};
template<typename T, int size> ZZ Myclass<T, size>::b;

#endif //TEMPLATE_H_