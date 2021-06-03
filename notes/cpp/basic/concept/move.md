## move concept
- Move semantics allows an object, under certain conditions, to take ownership of some other object's external resources.

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

## 
