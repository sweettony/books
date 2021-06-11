# Template type deduction
![image](./image/type-deduction-1.png)
<p></br></p>
<p></br></p>

1. [ParamType is a Pointer or a Reference](##%20ParamType%20is%20a%20Pointer%20or%20a%20Reference)  
2. [ParamType is a Universal Reference](##%20ParamType%20is%20a%20Universal%20Reference)
3. [ParamType is Neither a Pointer nor a Reference](##%20ParamType%20is%20Neither%20a%20Pointer%20nor%20a%20Reference)  
4. [Array Arguments](##%20Array%20Arguments)
5. [Function Arguments](##%20Function%20Arguments)
6. [Summary](##%20Summary)
7. [`auto`](##%20auto)

<p></br></p>
<p></br></p>

## ParamType is a Pointer or a Reference
- If expr’s type is a reference, ignore the reference part.Then pattern-match expr’s type against ParamType to determine T.
```c++
    template<typename T>
    void f(T& param);       // param is a reference
    int x = 27;             // x is an int
    const int cx = x;       // cx is a const int
    const int& rx = x;      // rx is a reference to x as a const int
    f(x);                   // T is int, param's type is int&

    f(cx);                  // T is const int,
                            // param's type is const int&
    f(rx);                  // T is const int,
                            // param's type is const int&
```

<p></br></p>

## ParamType is a Universal Reference
- see [perfect forward reference](../basic/concept/forward-reference.md)

<p></br></p>

## ParamType is Neither a Pointer nor a Reference
- That means that param will be a copy of whatever is passed in—a completely new object. The fact that param will be a new object motivates the rules that govern how T is deduced from expr.
- when passed argument is reference.
    - if expr’s type is a reference, ignore the reference part.
    - after ignoring expr’s reference-ness, expr is const, ignore that, too. If it’s volatile, also ignore that.
```c++
    template<typename T>
    void func(T v);
```

<p></br></p>

## Array Arguments
-  in many contexts, an array decays into a pointer to its first element. 
```c++
    //This decay is what permits code like this to compile:
    const char name[] = "J. P. Briggs";  // name's type is
                                         // const char[13]
    const char * ptrToName = name;       // array decays to pointer
```
-  What if an array is passed to a template taking a by-value parameter? What happens then? This equivalence of array and pointer parameters is a bit of foliage springing from the C roots at the base of C++, and it fosters the illusion that array and pointer types are the same.
```c++
    void myFunc(int param[]); //is equivalently declared like this
    void myFunc(int* param);         // same function as above

    int func(int cc[3]) //int func(int*)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return 0;
    }
```  
- Because array parameter declarations are treated as if they were pointer parameters, the type of an array that’s passed to a template function by value is deduced to be a pointer type. That means that in the call to the template f, its type parameter T is deduced to be const char*.
```c++
    template<typename T>
    void f(T val);
    f(name);          // name is array, but T deduced as const char*
```
- But Although functions can’t declare parameters that are truly arrays, they can declare **parameters that are references to arrays**!
```c++
    template<typename T>
    void f(T& param);      // template with by-reference parameter
    char name[] = "Jason Ye"
    f(name);          // name is array, T deduced as char (&)[9]

        // return size of an array as a compile-time constant. (The
    // array parameter has no name, because we care only about
    // the number of elements it contains.)
    template<typename T, std::size_t N>                 // see info
    constexpr std::size_t arraySize(T (&)[N]) noexcept  // below on
    {                                                   // constexpr
        return N;                                         // and
    }                                                   // noexcept

```
- Summary
```c++
    template<typename T>int func(T cc)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return 0;
    }
    template<typename T>int func1(T& cc)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return 0;
    }
    template<typename T>int func2(T* cc)
    {
        std::cout << __PRETTY_FUNCTION__ << '\n';
        return 0;
    }
    int main()
    {
        int bb[3];
        func(bb);
        func1(bb);
        func2(bb);
        return 0;
    }
    //out put
    //int func(T) [with T = int*]
    //int func1(T&) [with T = int [3]]
    //int func2(T*) [with T = int]
```
<p></br></p>

## Function arguments
- the same as array argument.

<p></br></p>

## Summary

| ID | Things to remember |
|:----|:-----------|
|1|During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness is ignored.|
|2|When deducing types for universal reference parameters, lvalue arguments get special treatment.|
|3|When deducing types for by-value parameters, const and/or volatile arguments are treated as non-const and non-volatile.|
|4|During template type deduction, arguments that are array or function names decay to pointers, unless they’re used to initialize references.|

<p></br></p>

## `auto`