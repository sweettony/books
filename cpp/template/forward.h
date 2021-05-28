#include <list>
#include <iostream>

class A;

typedef  std::list<A*>::iterator audio_iterator;

class B
{
public:

    B(){}
    ~B(){}
    std::list<A*> m_list;
};