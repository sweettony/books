#ifndef _TEMPLATE_SPEC_CLASS_
#include <iostream>

template <typename T>
class Demo
{
    public:
        Demo(){}
        ~Demo(){}
    public:
        void print()
        {
            std::cout << "print in Demo<T>" << std::endl;
        }
};

template<>
class Demo<int>
{
    public:
        Demo(){}
        ~Demo(){}
    public:
        void print();
};


#endif //_TEMPLATE_SPEC_CLASS_