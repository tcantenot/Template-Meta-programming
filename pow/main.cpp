#include <iostream>

#include "pow.hpp"

int main(int argc, char ** argv)
{
    if(argc > 1)
    {
        std::cout << "Computing " << atoi(argv[1]) << " times 2^100 : \n" << std::endl;
        Pow::benchmark(atoi(argv[1]));
    }
    else
    {
        std::cout << "./pow <loop_count>" << std::endl;
    }
    return 0;
}
