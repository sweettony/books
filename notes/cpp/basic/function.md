# Contents
- [unnamed parameter](Why-is-a-function-without-argument-identifiers-valid-in-C++?)



## Why is a function without argument identifiers valid in C++?
>it is for parameter that is unused     
>c++14  
[ 8.3.5.11] An identifier can optionally be provided as a parameter name; if present in a function definition , it names a parameter (sometimes called “formal argument”). [Note: In particular, parameter names are also optional in function definitions and names used for a parameter in different declarations and the definition of a function need not be the same.]
```c++
    这是C++iterator的operator函数
      _Self&
      operator++()
      {
	_M_node = _M_node->_M_next;
	return *this;
      }

      _Self
      operator++(int)
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_next;
	return __tmp;
      }

      _Self&
      operator--()
      {
	_M_node = _M_node->_M_prev;
	return *this;
      }

      _Self
      operator--(int)
      {
	_Self __tmp = *this;
	_M_node = _M_node->_M_prev;
	return __tmp;
      }  
````