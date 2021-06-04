## contents
## move concept
- Move semantics allows an object, under certain conditions, to **take ownership of some other object's external resources.**

## important in some ways
- turning expensive copies into cheap moves. except that an object does not manager any external resource.
- implementing safe "move-only" types; that is, types for which copying does not make sense but moving does. Examples include locks, file handles, and smart pointer with unique ownership semantics.

## what is move?

```c++
      +---------------+
      | triangle data |
      +---------------+
        ^
        |
        |
        |
  +-----|---+
  |   +-|-+ |
a | p | | | |
  |   +---+ |
  +---------+

      +---------------+
      | triangle data |
      +---------------+
        ^
        |
        +----------------------+
                               |
  +---------+            +-----|---+
  |   +---+ |            |   +-|-+ |
a | p |   | |          b | p | | | |
  |   +---+ |            |   +---+ |
  +---------+            +---------+
```
- in picture, the initialization of b with a does not copy the triangle, but instead transfers the ownership of the triangle from a to b. we also say "a is move into b" or "the triangle is move from a to b".
- **To move an object means to transfer ownership of some resource it manages to another object.**

## dangerous and harmless moves
- **dangerous**
```c++
    auto_ptr<Shape> a(new Triangle);   // create triangle
    auto_ptr<Shape> b(a);              // move a into b
    double area = a->area();           // undefined behavior
```
- **harmful**
```c++
    auto_ptr<Shape> make_triangle()
    {
        return auto_ptr<Shape>(new Triangle);
    }
    auto_ptr<Shape> c(make_triangle());      // move temporary into c
    double area = make_triangle()->area();   // perfectly safe
```  
<p>&nbsp;</p>

## why it is dangerous or harmless
- a is an example of an lvalue, whereas make_triangle() is an example of an rvalue.
- Moving from lvalues such as a is dangerous, because we could later try to call a member function via a, invoking undefined behavior. On the other hand, moving from rvalues such as make_triangle() is perfectly safe, because after the copy constructor has done its job, we cannot use the temporary again. 
<p>&nbsp;</p>

## rvalue references
- why we need this?
    - In order to distinguish lvalue arguments from rvalue arguments.
    - Solve the problem that moving from lvalue.
- concept
    - **An rvalue reference is a new kind of reference that only binds to rvalues**, and the syntax is `X&&`.
    - The good old reference X& is now known as an lvalue reference.
- const  
    - If we throw const into the mix, we already have four different kinds of references. What kinds of expressions of type X can they bind to?
    - diagram
```c++
                lvalue   const lvalue   rvalue   const rvalue
    ---------------------------------------------------------              
    X&          yes
    const X&    yes      yes            yes      yes
    X&&                                 yes
    const X&&                           yes      yes
```
- **implicit conversion**
    - Rvalue references went through several versions. Since version 2.1, an rvalue reference X&& also binds to all value categories of a different type Y, provided there is an implicit conversion from Y to X. In that case, a temporary of type X is created, and the rvalue reference is bound to that temporary.
    <p>&nbsp;</p>

    *In the below example, "hello world" is an lvalue of type const char[12]. Since there is an implicit conversion from const char[12] through const char* to std::string, a temporary of type std::string is created, and r is bound to that temporary. This is one of the cases where the distinction between rvalues (expressions) and temporaries (objects) is a bit blurry.*

```c++
    void some_function(std::string&& r);
    some_function("hello world");
```
    
## move constructors
- A useful example of a function with an `X&&` parameter is the move constructor `X::X(X&& source)`. Its purpose is to transfer ownership of the managed resource from the source into the current object.  
*The second line fails to compile, because a is an lvalue, but the parameter unique_ptr&& source can only be bound to rvalues. This is exactly what we wanted; dangerous moves should never be implicit. The third line compiles just fine, because make_triangle() is an rvalue. The move constructor will transfer ownership from the temporary to c. Again, this is exactly what we wanted.*
```c++
    unique_ptr(unique_ptr&& source)   // note the rvalue reference
    {
        ptr = source.ptr;
        source.ptr = nullptr;
    }
    unique_ptr<Shape> a(new Triangle);
    unique_ptr<Shape> b(a);                 // error
    unique_ptr<Shape> c(make_triangle());   // okay
```

## move assignment
```c++
    unique_ptr& operator=(unique_ptr&& source)   // note the rvalue reference
    {
        if (this != &source)    // beware of self-assignment
        {
            delete ptr;         // release the old resource

            ptr = source.ptr;   // acquire the new resource
            source.ptr = nullptr;
        }
        return *this;
    }

  /**
   *  @brief Swaps two values.
   *  @param  __a  A thing of arbitrary type.
   *  @param  __b  Another thing of arbitrary type.
   *  @return   Nothing.
  */
  template<typename _Tp>
    inline void
    swap(_Tp& __a, _Tp& __b)
#if __cplusplus >= 201103L
    noexcept(__and_<is_nothrow_move_constructible<_Tp>,
	            is_nothrow_move_assignable<_Tp>>::value)
#endif
    {
      // concept requirements
      __glibcxx_function_requires(_SGIAssignableConcept<_Tp>)

      _Tp __tmp = _GLIBCXX_MOVE(__a);
      __a = _GLIBCXX_MOVE(__b);
      __b = _GLIBCXX_MOVE(__tmp);
    }

    unique_ptr& operator=(unique_ptr source)   // note the missing reference
    {
        std::swap(ptr, source.ptr);
        return *this;
    }
```

## moving from lvalues
- `std::move()`
    - **casts an lvalue to an rvalue, thus enabling a subsequent move.**

## Xvalues
- Note that even though std::move(a) is an rvalue, its evaluation does not create a temporary object. This conundrum forced the committee to introduce a third value category. Something that can be bound to an rvalue reference, even though it is not an rvalue in the traditional sense, is called an xvalue (eXpiring value). The traditional rvalues were renamed to prvalues (Pure rvalues). Both prvalues and xvalues are rvalues. Xvalues and lvalues are both glvalues (Generalized lvalues). The relationships are easier to grasp with a diagram:
```c++
        expressions
          /     \
         /       \
        /         \
    glvalues   rvalues
      /  \       /  \
     /    \     /    \
    /      \   /      \
lvalues   xvalues   prvalues
```
## Moving out of functions
- Function return by value. some objects(probably a local variable or a temporary, but could be any kind of object) at call site is initialized with the expression after the return statement as an argument to move constructor.
```c++
    unique_ptr<Shape> make_triangle()
    {
        return unique_ptr<Shape>(new Triangle);
    }          \-----------------------------/
                    |
                    | temporary is moved into c
                    |
                    v
    unique_ptr<Shape> c(make_triangle());
```
- Surprised that automatic objects(local variable not declared as `static`) can also be implicitly moved out of functions
    - How come the move constructor accept the lvalue `result` as argument?
        - The scope of `result` is about to end, and it will be destroyed during stack unwinding. Nonbody will complain afterward that `result` has changed somehow.
        - When control flow is back at caller, the `result` does not exist anymore.
        - For those reasons, C++11 has special rules that allows returning automatic objects without having to write `std::move()`
        - In fact, you should never use `std::move` to move automatic objects out of functions, as this inhibits the "named return value optimization" (NRVO).
```c++
    unique_ptr<Shape> make_square()
    {
        unique_ptr<Shape> result(new Square);
        return result;   // note the missing std::move
    }
```
- **Return type is a value, not a rvalue reference**.
    - Rvalue references are still references, and as always, you should never return a reference to an automatic object; the caller would end up with a dangling reference if you tricked the compiler into accepting your code, like this:
    - **Never return automatic objects by rvalue reference.** Moving is exclusively performed by the move constructor, not by std::move, and not by merely binding an rvalue to an rvalue reference.
```c++
    unique_ptr<Shape>&& flawed_attempt()   // DO NOT DO THIS!
    {
        unique_ptr<Shape> very_bad_idea(new Square);
        return std::move(very_bad_idea);   // WRONG!
    }
```
    
## Moving into member
- **A named rvalue reference is an lvalue, just like any other variable.**
    - the compiler will complain that `parameter` is an lvalue. If you look at its type, you see an rvalue reference, but an rvalue reference simply means "a reference that is bound to an rvalue"; it does not mean that the reference itself is an rvalue! Indeed, `parameter` is just an ordinary variable with a name. You can use `parameter` as often as you like inside the body of the constructor, and it always denotes the same object. Implicitly moving from it would be dangerous, hence the language forbids it.
    - You can also pass the parameter by value. For move-only types like unique_ptr, it seems there is no established idiom yet. Personally, I prefer to pass by value, as it causes less clutter in the interface.
```c++
    class Foo
    {
        unique_ptr<Shape> member;

    public:

        Foo(unique_ptr<Shape>&& parameter)
        : member(parameter)   // error
        {}
    };
```

## unified assignment
```c++
    X& X::operator=(X source)    // unified assignment operator
    {
        swap(source);            // see my first answer for an explanation
        return *this;
    }
    // 1. the argument is lvalue.
    // copy construcor call----> swap using move sementic
    // 2. the argument is rvalue
    // move construcor call----> swap using move sementic
```
## forwarding reference
- see forward-reference.md

## implementation of `move`
- As you can see, move accepts any kind of parameter thanks to the forwarding reference T&&, and it returns an rvalue reference. The `std::remove_reference<T>::type` meta-function call is necessary because otherwise, for lvalues of type X, the return type would be X& &&, which would collapse into X&. Since t is always an lvalue (remember that a named rvalue reference is an lvalue), but we want to bind t to an rvalue reference, we have to explicitly cast t to the correct return type. The call of a function that returns an rvalue reference is itself an xvalue. Now you know where xvalues come from ;)
- The call of a function that returns an rvalue reference, such as `std::move`, is an xvalue.
```c++
    template<typename T>
    typename std::remove_reference<T>::type&&
    move(T&& t)
    {
        return static_cast<typename std::remove_reference<T>::type&&>(t);
    }
```