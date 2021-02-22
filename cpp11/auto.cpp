#include <iostream>

class myclass
{
private:
    
public:
    myclass();
    ~myclass();
public:
    void begin();
    void begin() const;
private:
    int m_a;
};
void myclass::begin()
{
    std::cout << "in begin" << std::endl;
}

void myclass::begin() const
{
    std::cout << "in cbegin" << std::endl;
}

myclass::myclass()
{

}

myclass::~myclass()
{
}
// template<typename T>
// constexpr auto add(T x, T y) -> decltype(x)
// {
//     return x+y;
// }

template<int N>
class fixed_size_list
{ /*...*/ };


constexpr int add(int x, int y){ return x+y;}

int main()
{
    const int a = 5;
    const int b = 4;
    const int* const c = &b;
    //c = &a;
    int array[add(a, b)];
    return 0;
}