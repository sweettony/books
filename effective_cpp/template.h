#ifndef TEMPLATE_H_
#define TEMPLATE_H_
#include <iostream>


template<typename T>int func(const T& val)
{
    std::cout << "i love you" << std::endl;
    return 0;
}


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
};

template<typename T, int size> T Myclass<T, size>::a[size] = {size};

#endif //TEMPLATE_H_