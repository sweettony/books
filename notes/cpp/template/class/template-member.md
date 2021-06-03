# Contents

- [How to implement copy and assignment member fuction](#member-fucntion)
- [Stop compiler to generate default copy function and others](#default-function)

## member function
>1. copy ctor  
```c++
    template<typename T>
    class SmartPtr {
        public:
        template<typename U> // member template
        SmartPtr(const SmartPtr<U>& other); // for a ”generalized
        ... // copy constructor”
    };
```

* Constructors like this ones that create one object from another object whose type is a different instantiation of the same template (e.g., create a `SmartPtr<T>` from a `SmartPtr<U>`) are sometimes known as generalized copy constructors  
* As declared, the generalized copy constructor for SmartPtr offers more
than we want. such as int -> short  

 ```c++
    template<typename T>
    class SmartPtr {
    public:
        template<typename U>
        SmartPtr(const SmartPtr<U>& other) // initialize this held ptr
        : heldPtr(other.get()) { ... } // with other’s held ptr
        T* get() const { return heldPtr; }
        ...
    private: // built-in pointer held
        T *heldPtr; // by the SmartPtr
    };
```
*  we can use the implementation of the constructor template to restrict the conversions to those we want.  


>2. assignment function
* the same as copy ctor
```c++
    template<typename T>
    class SmartPtr {
    public:
        template<typename U>
        SmartPtr& operator=(const SmartPtr<U>& other);
    };
```

## default function
* how to stop compiler to generator default fucntions. you must declare two different member functions the same time.  
```c++
    template<typename T>
    class Demo
    {
    public:
        Demo(const Demo& r);
        template<typename U>
        Demo(const Demo<U>& r)
    }
```

## friend function
* how to wirte friend function of class template  
    * No.1  
``` c++ 
    template <typename T> class A;
    template <typename T> A<T> function(const A<T>& l , const A<T>& r);
    template <typename T> class A
    {
        //template instance, cannot definition and need forward declaration.
        friend A<T> function<T>(const A<T>& l , const A<T>& r); 
    };
    template <typename T> A<T> function(const A<T>& l , const A<T>& r)
    {
        ...
    }  
```
*    * No.2
``` c++ 
    template <typename T> class A
    {
        friend A function(const A& l , const A& r)
        {
            ...
        }
    };
``` 
