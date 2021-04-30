#include "stdio.h"

struct aa
{
    
};

struct bb
{
    
};


class A
{
public:
    typedef struct aa category;
    A(){}
    ~A(){}
};


class B
{
public:
    typedef struct bb category;
    B(){}
    ~B(){}
};

//---------------------------------------
void set(A a, struct aa)
{
    printf("in a\n");
    return;
}
void set(B a, struct bb)
{
    printf("in b\n");
    return;
}
template<typename T> void set(T& t)
{
    set(t, typename T::category());
    return;
}

int main()
{
    A a;
    B b;
    set<A>(a);
    set<B>(b);
    return 0;
}
