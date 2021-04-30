#include <string>
#include <iostream>
class Myclass
{
private:
    std::string m_str1;
    std::string m_str2;
public:
    Myclass();

    ~Myclass()
    {
        std::cout << "---------------------" << std::endl;
    }
};

inline int func2()
{
    std::cout << "---------------------func2" << std::endl;
    return 4;
}

Myclass::Myclass()
{
    m_str1 = '3';
    m_str1 = '4';
}

int main()
{
    Myclass zz;
    func2();
    int (*p)() = &func2;
    p();
    return 0;
}