#include <iostream>
class Myclass
{
private:

public:
    Myclass();
    ~Myclass();
};

Myclass::Myclass()
{
    std::cout << "------------------------in construct" << std::endl;
}

Myclass::~Myclass()
{
    std::cout << "------------------------in destruct" << std::endl;
}

Myclass&& func()
{
    Myclass a;
    return std::move(a);
}

Myclass func_copy()
{
    Myclass a;
    return a; 
}
int main()
{
    Myclass&& a = func();
    Myclass   b = func_copy();
    return 0;
}