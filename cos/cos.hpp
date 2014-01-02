#ifndef COS_HPP
#define COS_HPP

#include "../pow/pow.hpp"
#include "../factorial/factorial.hpp"

#include <iostream>
#include <chrono>
#include <cmath>

static double constexpr TO_RAD = M_PI / 180.0;

// N or n is the order => precision of the result

//==============================================================================
// Function cosinus
//==============================================================================
namespace Normal {

    double Cos(double x, int n)
    {
        return n == 0 ? 1.0 : Cos(x, n - 1) + (n % 2 ? -1.0 : 1.0) *
            Pow(x, 2 * n) / Factorial(2 * n);
    }

}
//==============================================================================
// Inline function cosinus
//==============================================================================
namespace Inline {

    inline double Cos(double x, int n)
    {
        return n == 0 ? 1.0 : Cos(x, n - 1) + (n % 2 ? -1.0 : 1.0) *
            Pow(x, 2 * n) / Factorial(2 * n);
    }

}

//==============================================================================
// Inline template function cosinus
//==============================================================================
namespace RecursiveTemplateFunc {

    template <int N>
    inline double Cos(double x)
    {
        return Cos<N - 1>(x) + (N % 2 ? -1.0 : 1.0) * Pow<2 * N>(x) /
            Factorial<2 * N>();
    }

    template <>
    inline double Cos<0>(double)
    {
        return 1.0;
    }
}

//==============================================================================
// Recursive struct cosinus
//==============================================================================
namespace RecursiveTemplateStruct {

    template <int X, int N>
    struct Cos
    {
        static const double Value;
    };

    template <int X, int N>
    double const Cos<X, N>::Value = Cos<X, N - 1>::Value + (N % 2 ? -1.0 : 1.0) *
        std::pow(X * TO_RAD, 2 * N) / Factorial<2 * N>::Value;

    template <int X>
    struct Cos<X, 0>
    {
        static const double Value;
    };

    template <int X>
    double const Cos<X, 0>::Value = 1.0;

}
//==============================================================================
// Constexpr Function cosinus
//==============================================================================
namespace Constexpr {

    constexpr double Cos(double x, int n)
    { 
        return n == 0 ? 1.0 : Cos(x, n - 1) + Pow(-1, n) * Pow(x, 2 * n) /
            Factorial(2 * n);
    }

}

//==============================================================================
// Compile-time generated array of cosinus
//==============================================================================
static std::size_t const COS_ARRAY_SIZE = 181u;

namespace CompileTimeArray {

static auto cos_func = [](int const & v)
{
    return std::cos(v * TO_RAD);
};

template <int SIZE, int N = SIZE - 1>
struct CosTable : public CosTable<SIZE, N - 1>
{
    static int const recursion;
};

template <int SIZE, int N>
int const CosTable<SIZE, N>::recursion = CosTable<SIZE, 0>::array[N]
    = cos_func(N) + 0 * CosTable<SIZE, N - 1>::recursion;

template <int SIZE>
struct CosTable<SIZE, 0>
{
    static double array[SIZE];

    static int const recursion;
};

template <int SIZE>
double CosTable<SIZE, 0>::array[SIZE] = { cos_func(0) };

template struct CosTable<COS_ARRAY_SIZE>;

static double const * cosinus = CosTable<COS_ARRAY_SIZE>::array;

}

//==============================================================================
// Minimalist benchmark
//==============================================================================
namespace Cos {

    void benchmark(int n)
    {
        std::cout << Normal::Cos(45 * TO_RAD, 100) << std::endl;
        std::cout << Inline::Cos(45 * TO_RAD, 100) << std::endl;
        std::cout << RecursiveTemplateFunc::Cos<100>(45 * TO_RAD) << std::endl;
        std::cout << RecursiveTemplateStruct::Cos<45, 100>::Value << std::endl;
        std::cout << CompileTimeArray::cosinus[45] << std::endl;
        std::cout << Constexpr::Cos(45 * TO_RAD, 50) << std::endl;
        std::cout << std::cos(45 * TO_RAD) << std::endl;
        std::cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto c = Normal::Cos(45 * TO_RAD, 100);
        } 
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Normal : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto c = Inline::Cos(45 * TO_RAD, 100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Inline : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto c = RecursiveTemplateFunc::Cos<100>(45 * TO_RAD);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template func : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto f = RecursiveTemplateStruct::Cos<45, 100>::Value;
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template struct : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto c = CompileTimeArray::cosinus[45];
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Compile-time array : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            // With constexpr, the value is computed at compile time.
            // Without, the value is dynamically computed.
            constexpr auto c = Constexpr::Cos(45 * TO_RAD, 50);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Constexpr : " << dur.count() << "ms" << std::endl;
    }

}

#endif //COS_HPP
