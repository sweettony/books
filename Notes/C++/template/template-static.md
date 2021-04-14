# hi md

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

````