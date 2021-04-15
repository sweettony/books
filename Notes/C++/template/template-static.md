
# Contents

<font size = 5>

1. [Static member](#static&nbsp;member)
    - <font size = 4> [Example code](#example-code) </font>
</font>




## static member

### example code


```c++
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
````


>static 在父类中共享；在子类不共享
