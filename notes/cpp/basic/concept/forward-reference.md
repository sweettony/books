# Universal References


## two meaning of `&&`
- Rvalue reference
```c++
    void function(int&& val);
```
- Universal reference
```c++
    template<typename T>
    void function(T&& val);

    auto&& val = 9;
```
- Demo
```c++
    template<typename T>
    void function(T&& val);

    auto&& val = 9;
```
  
## How to distinguish two types of "&&".
- **Key point.**
  - The essence of the issue is that “&&” in a `type declaration` sometimes means rvalue reference, but sometimes it means either rvalue reference or lvalue reference.
- When the "&&" is universal reference
    - If a variable or parameter is declared to have type T&& for some deduced type T, that variable or parameter is a universal reference.
        - **LIMITATION**: type deduction.( function template parameters)
        - Must be `T&&`; **can only occur in the form of `T&&`!**
        - Even the simple addition of a `const` qualifier is enough to disable the interpretaion as a universal reference.
    - If the expression initializing a universal reference is an lvalue, the universal reference becomes an lvalue reference.
    - If the expression initializing the universal reference is an rvalue, the universal reference becomes an rvalue reference.
    - How to distinguish the **value type** of expression
      - You can take the address of the expresssion.
      - The type of expresssion is lvalue reference.(rvalue reference is lvalue).
      - **temporary objects** or **implicit type conversions**.
- In type deduction.
  - So some occurrences of "&&" in source code may actually have meaning of "&" under some restricted circumstance/sərkəmˌstans/.
    - there’s no type deduction, there’s no universal reference.
```c++
    template<typename T>
    void f(T&& param);               // deduced parameter type ⇒ type deduction;
                                    // && ≡ universal reference
    
    template<typename T>
    class Widget {
        ...
        Widget(Widget&& rhs);        // fully specified parameter type ⇒ no type deduction;
        ...                          // && ≡ rvalue reference
    };
    // the use of constructor of Widget will cause the instantiation. and T has been known.
    template<typename T1>
    class Gadget {
        ...
        template<typename T2>
        Gadget(T2&& rhs);            // deduced parameter type ⇒ type deduction;
        ...                          // && ≡ universal reference
    };
    
    void f(Widget&& param);          // fully specified parameter type ⇒ no type deduction;
                                    // && ≡ rvalue reference
```
- 
