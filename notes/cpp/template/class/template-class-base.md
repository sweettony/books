## example 
```c++
    template<typename T>
    class Stack
    {
        void print(std::ostream out)
        {
            out << m_onne << '\n';
        }

        T m_none;
    };
``` 
## implementation of class template
- 使用说明
    - 在模板类里面，使用类名不需要在后面添加类型参数，默认使用模板参数
    - 模板类只能定义在命令空间和类里面，不能定义在函数和代码块里面
    - 在测c++17之前要使用模板类，必须明确指定类型参数。  

- Template installation.
    - **Partial usage of class template**: A class template usually applies multiple operations on the template arguments it is instantiated for. This might lead to impression that these template arguments have to provide all operations necessary for all member functions of a class template. But **this is not the case**: Template arguments only have to provide all operations that is needed.(instead of that could be need).  
    if `print` is not called, the template argument T does not have to support `operator <<`.  

- Concept
    - template argument must support operations that class template applies, this raise the question: how do we know which operation is required for a template to be able to get instantiated ? the term **concept** is often used to denote a set of constraints that is repeatly required in template library, for example, the c++ standard relies on such concepts as *random access iterator* and *default constructible*.
- Friend function
    - NO.1
    ```c++
        template<typename T>
        class Demo
        {
            friend template<typename U> int function(Demo<U> param); // this implementation will cause all T become Demo<int> friend function.
        };
    ```
    - NO.2
        ```c++
        template<typename T> class Demo;
        template<typename T> int function(Demo<T> param);
        
        template<typename T>
        class Demo
        {
            friend int function<>(Demo param); // this pattern inform this function is a template function.
        };
    ```
- Specilization
    - in g++, the compiler do not allow you specilize class or function in **different namespace**.
    - member function specilization should write in cpp file with `template<>` prefix
    - when define member function out of full specification class, U do not need `template<>` prefix