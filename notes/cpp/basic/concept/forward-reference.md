# Universal References
<p></br></p>

1. [universal reference](https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers)  
2. [Two meaning of `&&`](##%20Two%20;meaning%20;of%20;`&&`)  
3. [How to distinguish two types of `&&`](##%20How%20to%20distinguish%20two%20types%20of%20"&&")  
4. [`std::forward`](##%20`std::forward`)  
5. [Nitty Gritty Details](##%20Nitty%20Gritty%20Details)  
6. [`auto` type deduction](##%20`auto`%20type%20deduction)  
7. [`typedef`](##%20`typedef`)  
8. [`decltype`](##%20`decltype`)  

<p></br></br></p>

## Two meaning of `&&`
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
    template <typename T> int func(T&& c)  
    {  
        std::cout << __PRETTY_FUNCTION__ << std::endl;  
        return 0;  
    }  
    func(10);  
    int a = 3;  
    func(a);  
    int func(T&&) [with T = int]  
    int func(T&&) [with T = int&]  
```
  
## How to distinguish two types of `&&`.
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
    - There’s no type deduction, there’s no universal reference.
    - Lvalueness or rvalueness of an expression is independent of its type. 
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
## `std::forward`
- `std::forward` take a unniversial reference lvalue and convert it into an rvalue only if expresssion it's bound to an rvalue. The name of function is an acknowledgment that our desire to perform such a conversion is vritually always to perserve the calling argument's lvalueness or rvalueness when pass it to another function.

## Nitty Gritty Details
- Question
    - The true core of the issue is that some constructs in c++ 11 give rise to references to references, and references to references are not perimited in c++.
    - There are cases, however, where references to references arise as a result of type manipulations that take place during compilation, and in such cases, rejecting the code would be problematic. We know this from experience with the initial standard for C++, i.e., C++98/C++03.
```c++
    int b  = 3;
    auto& &a = b; // error!!! no such thing as "reference to reference"
```
- During type deduction for template parameter. 
    - If expresssion is lvalue, the T is T&
    - If expresssion is rvalue, the T is T
```c++
template <typename T> int func(T&& c)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}
// when c is initialized with the rvalue 10; the func like int func(int&& c)
// when c is initialized with the lvalue 10; the func like int func(int& && c)
```
- How to solve problem?
    - Because of the reference-to-reference, this instantiated code is prima facie invalid, but the source code– “f(x)” – is completely reasonable.  To avoid rejecting it, C++11 performs **“reference collapsing”** when references to references arise in contexts such as template instantiation.
    - Rules of thumb
        - Intro: Because there are two kinds of references (lvalue references and rvalue references), there are four possible reference-reference combinations: lvalue reference to lvalue reference, lvalue reference to rvalue reference, rvalue reference to lvalue reference, and rvalue reference to rvalue reference.  There are only two reference-collapsing rules:
        - An rvalue reference to an rvalue reference becomes (“collapses into”) an rvalue reference.
        - All other references to references (i.e., all combinations involving an lvalue reference) collapse into an lvalue reference.
        -  when deducing the type for a variable that is reference itself. in that case, the reference part is ignored. "see datagram 1.0"
```c++
    // datagram 1.0
    // deducing the type for a variable that is reference itself.
    int a = 3;
    int& lr  = a;
    int&& rr = std::move(a);
    func(lr);
    func(rr);
    //the type for both lr and r2 rr considered to be int in a call to the template f.  
    //This reference-stripping behavior is independent of the rule that, during type deduction for universal references,   
    //lvalues are deduced to be of type T& and rvalues of type T, so given these calls,
```

## `auto` type deduction
- the same as template type deduction

## `typedef`
- the same as template type deduction
## `decltype`
- The type-deduction rules employed by decltype are not the same as those used during template or auto type deduction.  
- `decltype` performs type deduction on expressions that yield types that are either T or T&
- given a named variable of non-reference type, deduces the type T (i.e., a non-reference type), while under the same conditions, templates and auto deduce the type T&.  Another important difference is that decltype’s type deduction depends only on the decltype expression; the type of the initializing expression (if any) is ignored

