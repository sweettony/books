#include <iostream>

template<typename T>
class base
{
    protected:
        base()
        {

        }
        ~base()
        {

        }
    protected:
        static T m_z;
};
template<typename T> T base<T>::m_z;


// template<>
// class base<int>
// {
//     protected:
//         base()
//         {

//         }
//         ~base()
//         {

//         }
//   };


template<typename T, int size>
class derived : public base<T>
{
    public:
        derived()
            :base<T>()
        {

        }
        ~derived()
        {

        }
    //using base<T>::m_z;
    T* get()
    {
        return &base<T>::m_z;
    }
    public:
        static T m_d;
};
template<typename T, int size> T derived<T, size>::m_d;

int main()
{
    derived<int, 9> c1;
    derived<int, 10> c2;
    std::cout << c1.get() << c2.get() << std::endl;
    std::cout << &c1.m_d << &c2.m_d << std::endl;
    return 0;
}