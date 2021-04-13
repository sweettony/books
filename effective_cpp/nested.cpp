#include <iostream>
static int s_int = 8;
class Myclass
{
public:
    class nested
    {
    private:
    public:
        nested(Myclass* pclass)
        {
            pclass->m_a = s_int;
            s_int++;
        }
        ~nested()
        {

        }
    };

private:
    nested m_cc;
    int m_a;

public:
    Myclass()
        :m_cc(this)
    {

    }
    ~Myclass()
    {
        
    }
    void print()
    {
        std::cout << m_a << std::endl;
    }
};


int main()
{

    Myclass zz;
    zz.print();
    Myclass::nested pp(&zz);
    zz.print();
    return 0;
}
