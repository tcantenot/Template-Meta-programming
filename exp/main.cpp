#include <iostream>

#include "exp.hpp"

int main(int argc, char ** argv)
{
    if(argc > 1)
    {
        std::cout << "Computing " << atoi(argv[1]) << " times exp(42) : \n" << std::endl;
        Exp::benchmark(atoi(argv[1]));
    }
    else
    {
        std::cout << "./exp <loop_count>" << std::endl;
    }
    return 0;
}
