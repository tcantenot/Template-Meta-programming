#ifndef POW_HPP
#define POW_HPP

#include <chrono>
#include <cmath>
#include <iostream>

//==============================================================================
// Function Power
//==============================================================================
namespace Normal {

    double Pow(double x, int n)
    {
        return n == 0 ? 1 : x * Pow(x, n - 1);
    }

}
//==============================================================================
// Inline function Power
//==============================================================================
namespace Inline {

    inline double Pow(double x, int n)
    {
        return n == 0 ? 1 : x * Pow(x, n - 1);
    }

}

//==============================================================================
// Inline template function Power
//==============================================================================
namespace RecursiveTemplateFunc {

    template <int N>
    inline double Pow(double x)
    {
        return x * Pow<N - 1>(x);
    }

    template <>
    inline double Pow<0>(double)
    {
        return 1.0;
    }

}

//==============================================================================
// Recursive struct Power
//==============================================================================
namespace RecursiveTemplateStruct {

    template <int X, int N>
    struct Pow
    {
        static const double Value;
    };

    template <int X, int N>
    double const Pow<X, N>::Value = static_cast<double>(X) * Pow<X, N - 1>::Value;

    template <int X>
    struct Pow<X, 0>
    {
        static const double Value;
    };

    template <int X>
    double const Pow<X, 0>::Value = 1.0;

}

//==============================================================================
// Constexpr Function Power
//==============================================================================
namespace Constexpr {

    constexpr double Pow(double x, int n)
    {
        return n == 0 ? 1.0 : x * Pow(x, n - 1);
    }

}

//==============================================================================
// Compile-time generated array of powers
//==============================================================================
static std::size_t const POW_ARRAY_SIZE = 500u;

namespace CompileTimeArray {

static auto pow_func = [](int const & v)
{
    return std::pow(2, v);
};

template <int SIZE, int N = SIZE - 1>
struct PowTable : public PowTable<SIZE, N - 1>
{
    static int const recursion;
};

template <int SIZE, int N>
int const PowTable<SIZE, N>::recursion = PowTable<SIZE, 0>::array[N]
    = pow_func(N) + 0 * PowTable<SIZE, N - 1>::recursion;

template <int SIZE>
struct PowTable<SIZE, 0>
{
    static double array[SIZE];

    static int const recursion;
};

template <int SIZE>
double PowTable<SIZE, 0>::array[SIZE] = { pow_func(0) };

template struct PowTable<POW_ARRAY_SIZE>;

static double const * powers = PowTable<POW_ARRAY_SIZE>::array;

}

//==============================================================================
// Minimalist benchmark
//==============================================================================
namespace Pow {

    void benchmark(int n)
    {
        std::cout << Normal::Pow(2, 100) << std::endl;
        std::cout << Inline::Pow(2, 100) << std::endl;
        std::cout << RecursiveTemplateFunc::Pow<100>(2) << std::endl;
        std::cout << RecursiveTemplateStruct::Pow<2, 100>::Value << std::endl;
        std::cout << CompileTimeArray::powers[100] << std::endl;
        std::cout << Constexpr::Pow(2, 100) << std::endl;
        std::cout << std::pow(2, 100) << std::endl;
        std::cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = Normal::Pow(2, 100);
        } 
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Normal : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = Inline::Pow(2, 100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Inline : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = RecursiveTemplateFunc::Pow<100>(2);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template func : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = RecursiveTemplateStruct::Pow<2, 100>::Value;
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template struct : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = CompileTimeArray::powers[100];
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Compile-time array : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            // With constexpr, the value is computed at compile time.
            // Without, the value is dynamically computed.
            constexpr auto p = Constexpr::Pow(2, 100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Constexpr : " << dur.count() << "ms" << std::endl;
    }

}

#endif //POW_HPP
