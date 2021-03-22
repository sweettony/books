#include <iostream>

class Base
{
private:
    
public:
    Base();
    ~Base();
    int base()
    {
        std::cout << "i am base " << std::endl;
    }
};

Base::Base()
{

}

Base::~Base()
{
}


class derived
    :public Base
{
private:
    
public:
    derived();
    ~derived();
    int der()
    {
        std::cout << "i am der " << std::endl;
    }

};

derived::derived()
{

}

derived::~derived()
{
}

int main()
{
    derived d;
    d.base();
    return 0;
}