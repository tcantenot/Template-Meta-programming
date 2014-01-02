#ifndef EXP_HPP
#define EXP_HPP

#include <chrono>
#include <cmath>
#include <iostream>

#include "../pow/pow.hpp"
#include "../factorial/factorial.hpp"

// N or n is the order => precision of the result

//==============================================================================
// Function Exponential
//==============================================================================
namespace Normal {

    double Exp_(double x, int n)
    {
        return n == 0 ? 1.0 : Exp_(x, n - 1) + Pow(x, n) / Factorial(n);
    }

    double Exp(double x, int n)
    {
        return x < 0.0 ? 1.0 / Exp_(-x, n) : Exp_(x, n);
    }

}
//==============================================================================
// Inline function Exponential
//==============================================================================
namespace Inline {

    inline double Exp_(double x, int n)
    {
        return n == 0 ? 1.0 : Exp_(x, n - 1) + Pow(x, n) / Factorial(n);
    }

    inline double Exp(double x, int n)
    {
        return x < 0.0 ? 1.0 / Exp_(-x, n) : Exp_(x, n);
    }

}

//==============================================================================
// Inline template function Exponential
//==============================================================================
namespace RecursiveTemplateFunc {


    template <int N>
    inline double Exp_(double x)
    {
        return Exp_<N - 1>(x) + Pow<N>(x) / Factorial<N>();
    }

    template <>
    inline double Exp_<0>(double)
    {
        return 1.0;
    }

    template <int N>
    inline double Exp(double x)
    {
        return x < 0.0 ? 1.0 / Exp_<N>(-x) : Exp_<N>(x);
    }

}

//==============================================================================
// Recursive struct Exponential
//==============================================================================
namespace RecursiveTemplateStruct {

    template <int X, int N>
    struct Exp_
    {
        static const double Value;
    };

    template <int X, int N>
    double const Exp_<X, N>::Value = Exp_<X, N - 1>::Value + Pow<X, N>::Value /
        Factorial<N>::Value;

    template <int X>
    struct Exp_<X, 0>
    {
        static const double Value;
    };

    template <int X>
    double const Exp_<X, 0>::Value = 1.0;

    template <int X, int N>
    struct Exp
    {
        static const double Value;
    };

    template <int X, int N>
    double const Exp<X, N>::Value = X < 0 ? 1.0 / Exp_<-X, N>::Value : 
                                            Exp_<X, N>::Value;
}

//==============================================================================
// Constexpr Function Exponential
//==============================================================================
namespace Constexpr {

    constexpr double Exp_(double x, int n)
    {
        return n == 0 ? 1.0 : Exp_(x, n - 1) + Pow(x, n) / Factorial(n);
    }

    constexpr double Exp(double x, int n)
    {
        return x < 0.0 ? 1.0 / Exp_(-x, n) : Exp_(x, n);
    }

}

//==============================================================================
// Compile-time generated array of exponentials
//==============================================================================
static std::size_t const EXP_ARRAY_SIZE = 500u;

namespace CompileTimeArray {

static auto exp_func = [](int const & v)
{
    return std::exp(v);
};

template <int SIZE, int N = SIZE - 1>
struct ExpTable : public ExpTable<SIZE, N - 1>
{
    static int const recursion;
};

template <int SIZE, int N>
int const ExpTable<SIZE, N>::recursion = ExpTable<SIZE, 0>::array[N]
    = exp_func(N) + 0 * ExpTable<SIZE, N - 1>::recursion;

template <int SIZE>
struct ExpTable<SIZE, 0>
{
    static double array[SIZE];

    static int const recursion;
};

template <int SIZE>
double ExpTable<SIZE, 0>::array[SIZE] = { exp_func(0) };

template struct ExpTable<EXP_ARRAY_SIZE>;

static double const * exponentials = ExpTable<EXP_ARRAY_SIZE>::array;

}

//==============================================================================
// Minimalist benchmark
//==============================================================================
namespace Exp {

    void benchmark(int n)
    {
        std::cout << Normal::Exp(42, 100) << std::endl;
        std::cout << Inline::Exp(42, 100) << std::endl;
        std::cout << RecursiveTemplateFunc::Exp<100>(42) << std::endl;
        std::cout << RecursiveTemplateStruct::Exp<42, 100>::Value << std::endl;
        std::cout << CompileTimeArray::exponentials[42] << std::endl;
        std::cout << Constexpr::Exp(42, 100) << std::endl;
        std::cout << std::exp(42) << std::endl;
        std::cout << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = Normal::Exp(42, 100);
        } 
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Normal : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = Inline::Exp(42, 100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Inline : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = RecursiveTemplateFunc::Exp<100>(42);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template func : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = RecursiveTemplateStruct::Exp<42, 100>::Value;
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Recursive template struct : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            auto p = CompileTimeArray::exponentials[100];
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Compile-time array : " << dur.count() << "ms" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        for(int i = 0; i < n; ++i)
        {
            // With constexpr, the value is computed at compile time.
            // Without, the value is dynamically computed.
            constexpr auto p = Constexpr::Exp(42, 100);
        }
        end = std::chrono::high_resolution_clock::now();
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Constexpr : " << dur.count() << "ms" << std::endl;
    }

}

#endif //EXP_HPP
