#include <iostream>

#include "factorial.hpp"

int main(int argc, char ** argv)
{
    if(argc > 1)
    {
        std::cout << "Computing " << atoi(argv[1]) << " times 100! : \n" << std::endl;
        Factorial::benchmark(atoi(argv[1]));
    }
    else
    {
        std::cout << "./factorial <loop_count>" << std::endl;
    }
    return 0;
}


