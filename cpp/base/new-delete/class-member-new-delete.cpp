#include <iostream>
#include <new>
#include <malloc.h>
void* operator new(size_t size) throw()
{
    std::cout << "in global new" << std::endl;
    return malloc(size);
}
void operator delete(void* p) throw()
{
    std::cout << "in global delete" << std::endl;
    return free(p);
}
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
    virtual ~base(){std::cout << "base dstor" << std::endl;}
    void print(){ std::cout << "hi" << std::endl;}
};

class derived : public base
{
public:
    static void operator delete(void* p, std::ostream& out) throw()
    {
        out << "delete in derived" << std::endl;
        derived* pDerived = static_cast<derived*>(p);
        pDerived->~derived();
        ::operator delete(pDerived);
        return;
    }
    static void operator delete(void* p) throw()
    {
        std::cout << "delete" << std::endl;
        ::operator delete(p);
        return;
    }
public:
    derived(){}
    ~derived(){ std::cout << "derived dstor" << std::endl; }
    void print(){ std::cout << "hi" << std::endl;}
};

int main()
{
    base* b = new derived();
    //derived::operator delete(b, std::cout);
    delete b;
    base* b1 = new base();
    delete b1;
    return 0;
}