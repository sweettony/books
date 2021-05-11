#include <iostream>
#include <exception>
#include <stdlib.h>
#include <memory>
#include <new>

//set_new_handler allows you to specify a function to be called when memory allocation requests cannot be satisfied.
//Nothrow new is of limited utility, because it applies only to memory allocation; associated constructor calls may still throw exceptions.

void new_handler()
{
    std::cout << "123" << std::endl;
    ::abort();
}

void fun()
{
    return;
} 


int main()
{
    //std::set_new_handler(new_handler);
    fun();
    void (*hun)() = fun;
    int* p = new int[102410241024];
    return 0;
}