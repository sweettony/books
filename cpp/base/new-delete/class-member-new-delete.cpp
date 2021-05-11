#include <iostream>

class base
{
public:
    static void operator delete(void* p, size_t len) throw()
    {
        std::cout << "delete " << len << " in base" << std::endl;
        ::operator delete(p);
        return;
    }
public:
    base(){}
    virtual ~base(){}
    void print(){ std::cout << "hi" << std::endl;}
};

class derived : public base
{
public:
    static void operator delete(void* p, size_t len) throw()
    {
        std::cout << "delete " << len << " in base" << std::endl;
        ::operator delete(p);
        return;
    }
public:
    derived(){}
    ~derived(){}
    void print(){ std::cout << "hi" << std::endl;}
};

int main()
{
    base* b = new derived();
    delete b;
    return 0;
}