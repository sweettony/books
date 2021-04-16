#include <list>
#include <iostream>
#include <math.h>
class base
{
public:
    base()
    {

    }
    ~base()
    {

    }
};

class derived : public base
{
public:
    derived()
        : base()
    {

    }
    ~derived()
    {
        
    }
};

template<typename T>
class TempClass
{
public:
    TempClass();
    ~TempClass();
public:
    //generalized copy constructors
    //non explicit note: That’s deliberate
    template<typename U> TempClass(const TempClass<U>& other);
    template<typename U> TempClass<T>& operator= (const TempClass<U>& other);
public:
    T data()const {return m_data;}
private:
    T m_data;
};

template<typename T> TempClass<T>::TempClass()
{

}

template<typename T> TempClass<T>::~TempClass()
{

}

template<typename T> template<typename U>  TempClass<T>::TempClass(const TempClass<U>& other)
    : m_data(other.data())
{

}

template<typename T> template<typename U> TempClass<T>& TempClass<T>::operator= (const TempClass<U>& other)
{
    //copy to temp
    //tmp move to this
    U data = other.data();
    m_data = data;
    return *this;
}

int main()
{
    // TempClass<int>       cc1;
    // TempClass<double>    cc2;
    // TempClass<int>       cc3 = cc2;
    // TempClass<double>    cc4 = cc1;

    TempClass<base*>    c1;
    TempClass<derived*> c2;
    TempClass<int*> c3;
    c1 = c2;
    c1 = c3;
    return 0;
}


//delete const pointer


#if 0 
    std::list<const int*> ll;
    int* p = new int;
    ll.push_back(p);
    const int* pp = ll.front();
    pp = p;
    delete pp;
#endif