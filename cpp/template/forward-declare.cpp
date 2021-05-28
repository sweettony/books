#include "forward.h"

class A
{
public:

    A();
    ~A();
    std::list<A*> m_list;
};

int main()
{
    B b;
    return 0;
}

