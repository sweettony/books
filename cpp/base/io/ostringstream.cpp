#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

template <typename T> std::string to_string( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

int  main()
{
    int val = 8;
    std::ostringstream oss;
    oss << 8;
    std::string str_val = oss.str();
    std::cout << str_val << std::endl;
    str_val = to_string<int>(8);
    std::cout << str_val << std::endl;
    printf("%x\n", str_val[0]);
    return 0;
}