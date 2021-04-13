# include <iostream>

class Myclass
{
private:

public:
    Myclass();
    ~Myclass();
public:
    // only interface, abstract class
    virtual int a() = 0;
    //interface and default implementation
    virtual int b();
    //interface and mandatory implementation
    int c();
private:
    void default_b()
    {
        return;    
    }
};

int main()
{
#if ZZ
    std::cout << "zzzz" << std::endl;
#endif

    return 0;
}
