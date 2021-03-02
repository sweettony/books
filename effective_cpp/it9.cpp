#include <iostream>
#include <stdio.h>
class Myclass
{
private:
    int m_a;
public:
    Myclass();
    ~Myclass();
    Myclass(const Myclass& op);
};

Myclass::Myclass(const Myclass& op)
{
    std::cout << "in copy" << std::endl;
}

Myclass::Myclass()
{
    std::cout << "in construction" << std::endl;
}

Myclass::~Myclass()
{
    std::cout << "in destruction" << std::endl;
}

const Myclass& func()
{
    Myclass c;
    return c;
}

const Myclass& func1()
{
    return Myclass();
}

Myclass func2()
{
    Myclass c;
    return c;
}

const Myclass& func3()
{
    return func2();
}


int main()
{
    // const Myclass& ref  = func();
    // const Myclass& ref1 = func1();
    const Myclass& ref2 = func2();
    printf("-----------------------ref2 = %p\n", &ref2);
    //const Myclass& ref3 = func3();
    //const Myclass  obj  = func2();
    return 0;
}