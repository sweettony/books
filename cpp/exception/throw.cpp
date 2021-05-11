#include <exception>
#include <iostream>
//Guarantee that functions will only throw listed exceptions (possibly none).
//Enable compiler optimizations based on the knowledge that only listed exceptions (possibly none) will be thrown.
int func() throw()
{
    return 1;
}

int hunc() throw(int, float)
{
    return func();
}


int main()
{

    int var = hunc();
    return var;
}