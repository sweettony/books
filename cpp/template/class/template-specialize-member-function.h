#ifndef _TEMPLATE_SPEC_MEMFUNCTION_
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
#endif //_TEMPLATE_SPEC_MEMFUNCTION_