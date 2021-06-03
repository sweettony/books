## lvalue
- lvalue has name and memory address.
- **rvalue reference** is lvalue
- **string literal**   is lvalue, but that is read-only.
## xvalue
- rvalue reference point to.
- using std::move to convert lvalue to xvalue.
## prvalue
- **temporary object** that you can not get address.