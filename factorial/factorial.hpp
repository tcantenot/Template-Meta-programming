#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <iostream>
#include <chrono>
#include <cmath>

//==============================================================================
// Function Factorial
//==============================================================================
namespace Normal {

    double Factorial(int n)
    {
        return n == 0 ? 1.0 : n * Factorial(n - 1);
    }

}
//==============================================================================
// Inline function Factorial
//==============================================================================
namespace Inline {

    inline double Factorial(int n)
    {
        return n == 0 ? 1.0 : n * Factorial(n - 1);
    }

}

//==============================================================================
// Inline template function Factorial
//==============================================================================
namespace RecursiveTemplateFunc {

    template <int N>
    inline double Factorial()
    {
        return N * Factorial<N - 1>();
    }

    template <>
    inline double Factorial<0>()
    {
        return 1.0;
    }

}

//==============================================================================
// Recursive struct Factorial
//==============================================================================
namespace RecursiveTemplateStruct {

    template <int N>
    struct Factorial
    {
        static const double Value;
    };

    template <int N>
    double const Factorial<N>::Value = N * Factorial<N - 1>::Value;

    template <>
    struct Factorial<0>
    {
        static const double Value;
    };

    double const Factorial<0>::Value = 1.0;

}

//==============================================================================
// Constexpr Function Factorial
//==============================================================================
namespace Constexpr {

    constexpr double Factorial(int n)
    {
        return n == 0 ? 1.0 : n * Factorial(n - 1);
    }

}

//==============================================================================
// Compile-time generated array of factorials
//==============================================================================

static std::size_t const FACT_ARRAY_SIZE = 500u;

namespace CompileTimeArray {

    template <int N, int I = N - 1>
    struct Table : public Table<N, I - 1>
    {
        static double const value;
    };

    template <int N, int I>
    double const Table<N, I>::value = Table<N, 0>::array[I]
                                    = I * Table<N, I - 1>::value;

    template <int N>
    struct Table<N, 0>
    {
        static double const value;
        static double array[N];
    };

    template <int N>
    double const Table<N, 0>::value = 1; // Initial value (I = 0)

    template <int N>
    double Table<N, 0>::array[N] = { Table<N, 0>::value }; // Initial value (I = 0)

    template struct Table<FACT_ARRAY_SIZE>;

    static double const * factorials = Table<FACT_ARRAY_SIZE>::array;

}

//==============================================================================
// Minimalist benchmark
//==============================================================================
namespace Factorial {

    void benchmark(int n)
    {
        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto f = Normal::Factorial(100);
        } 
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Normal : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto f = Inline::Factorial(100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Inline : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto f = RecursiveTemplateFunc::Factorial<100>();
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template func : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto f = RecursiveTemplateStruct::Factorial<100>::Value;
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template struct : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            // NB: The test is a little bit harder for the compile-time array
            //auto f = CompileTimeArray::factorials[i % FACT_ARRAY_SIZE];
            auto f = CompileTimeArray::factorials[100];
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Compile-time array : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            // With constexpr, the value is computed at compile time.
            // Without, the value is dynamically computed.
            constexpr auto f = Constexpr::Factorial(100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Constexpr : " << dur.count() << "ms" << std::endl;
    }

}

#endif //FACTORIAL_HPP
