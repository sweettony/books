# Template type deduction
![image](./image/type-deduction-1.png)
<p></br></p>
<p></br></p>

2. [ParamType#is#Neither#a#Pointer#nor#a#Reference]
1. [Array Arguments](##%20Array%20Arguments)

<p></br></p>
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
