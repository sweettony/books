#include <sstream>
#include <iostream>


int main()
{
    std::string duration = "11";
    std::stringstream ss;
    int interval = 0;
    ss << duration;
    ss >> interval;
    std::cout << duration << " " << interval << std::endl;
    return 0;
}