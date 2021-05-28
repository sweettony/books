# Contents

## 强转变量
* 在函数调用的过程中有可能会出现类型不匹配的情况；这个时候会强转。但强转会出现临时变量
```c++  

    int cc(void*&); // pass pointer of type int; int*---->void* will gennerate a temp pointer, and non-const reference can not refer temp variable
```