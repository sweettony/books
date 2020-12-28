/**
 * desconstructor cannot emit exception
 **/
#include <iostream>
class Myclass
{
private:
    /* data */
    int a;
public:
    Myclass(/* args */){
    std::cout << "constructor" << std::endl; 
}
    ~Myclass(){
    std::cout << "desconstructor" << std::endl;
}
    void zz(){ std::cout << __FUNCTION__ << std::endl; }
};
void func()
{
    std::cout << "1" << std::endl;
    Myclass zz1;
    std::cout << "2" << std::endl;
    try
    {
        Myclass zz;
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


