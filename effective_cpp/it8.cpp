/**
 * desconstructor cannot emit exception
 **/

#include <iostream>

class Myclass
{
private:
    /* data */
    int m_a;
public:
    Myclass(int a){
    std::cout << "constructor " << a << std::endl;
    m_a = a;
}
    ~Myclass(){
    std::cout << "desconstructor " << m_a << std::endl;
}
    void zz(){ std::cout << __FUNCTION__ << std::endl; }
};
void func()
{
    std::cout << "1" << std::endl;
    Myclass zz1(1);
    std::cout << "2" << std::endl;
    try
    {
        Myclass zz(2);
        throw 1;
    }
    catch(Myclass& zz)
    {
         std::cerr << "zzzzzzzzzzzzzzzzz" << '\n';
    }
    return;
}
int main()
{
    try
    {
        func();
    }
    catch(...)
    {
         std::cerr << "111111zzzzzzzzzzzzzzzzz" << '\n';
    }
}


