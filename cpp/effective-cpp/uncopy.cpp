#include <iostream>
class Uncopy
{

protected:
    Uncopy(){}
    ~Uncopy(){}
protected:
    Uncopy(const Uncopy& rhs);
    Uncopy& operator=(const Uncopy& rhs){ std::cout << "in father" << std::endl; }
    void cc(){ std::cout << "in zz father" << std::endl; }
    void cc(int a){ std::cout << "in zz1 father" << std::endl; }
};


class zz
    : private Uncopy
{

public:
    zz(int a)
    {
        cc();
        m_a = a;
    }
    ~zz()
    {

    }
    void bb(){ }
private:
    int m_a;
};



int main()
{
    Uncopy *pclass_uncopy = new zz(0);
    return 0;
}
