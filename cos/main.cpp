#include <iostream>

#include "cos.hpp"

int main(int argc, char ** argv)
{
    if(argc > 1)
    {
        std::cout << "Computing " << atoi(argv[1]) << " times cos(45) : \n" << std::endl;
        Cos::benchmark(atoi(argv[1]));
    }
    else
    {
        std::cout << "./cos <loop_count>" << std::endl;
    }
    return 0;
}
