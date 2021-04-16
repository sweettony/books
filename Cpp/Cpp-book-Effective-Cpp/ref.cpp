#include <iostream>

class Myclass
{
private:
    /* data */
    int a;
public:
    Myclass(/* args */);
    ~Myclass();
    void set(int b)
    {
        a = b;
    }

};

Myclass::Myclass()
{
    std::cout << "----constuctor" << std::endl;
}

Myclass::~Myclass()
{
    std::cout << "----destuctor" << std::endl;
}

Myclass&& func()
{
    Myclass a;
    return std::move(a);
}

Myclass __attribute__((optimize("O0"))) func1()
{
    Myclass a;
    a.set(10);
    std::cout << "addr = " << &a << std::endl;
    return a;
}

int main()
{
    int c;
    Myclass&& zz = func();
    Myclass cc = func1();
    std::cout << "addr = " << &cc << std::endl;
    std::cin >> c;
    return 0;
}
