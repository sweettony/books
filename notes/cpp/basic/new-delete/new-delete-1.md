# outline
> this article is intros to replacable new and delete.  

# Contents
- [reasons](reasons)
- [replacable operator signature](signature-of-new-and-delete)
- [static member function](member-function)


## reasons
> to detect usage errors  
1. using more than one delete on newed memory.
2. data overruns and underruns  


## signature of new and delete

for global new and delete
````c++
        void* operator new(std::size_t) _GLIBCXX_THROW (std::bad_alloc)
    __attribute__((__externally_visible__));
    void* operator new[](std::size_t) _GLIBCXX_THROW (std::bad_alloc)
    __attribute__((__externally_visible__));
    void operator delete(void*) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
    void operator delete[](void*) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
    void* operator new(std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
    void* operator new[](std::size_t, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
    void operator delete(void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
    void operator delete[](void*, const std::nothrow_t&) _GLIBCXX_USE_NOEXCEPT
    __attribute__((__externally_visible__));
````
for class-specific new and delete
````c++
    void T::operator delete  ( void* ptr );
    void T::operator delete[]( void* ptr );
    void T::operator delete  ( void* ptr, std::align_val_t al );
    void T::operator delete[]( void* ptr, std::align_val_t al );
    void T::operator delete  ( void* ptr, std::size_t sz );
    void T::operator delete[]( void* ptr, std::size_t sz );
    void T::operator delete  ( void* ptr, std::size_t sz, std::align_val_t al );
    void T::operator delete[]( void* ptr, std::size_t sz, std::align_val_t al );
````
>these signatures is what you can replace. when u use keyword new and delete, it will call your custom new and delete operator function.  

## member function
>In class; operator new and delete is static member function. and you must provide custom operator new and delete together. Because when the exception happen in cstor function and then throw exception, the runtime system is resposible to recycle the allocated memory. it find delete according operator new signature.
