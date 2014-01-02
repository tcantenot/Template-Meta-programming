# EXP

## How to use it

    * **make** or **make opt**
    * ./exp <loop_count>

    Computes <loop_count> times exp(42).

## Results

    ./exp 1000000

    (exp(42) = 1.73927e+18)

    Without optimizations:

        Normal : 117588ms
        Inline : 117950ms
        Recursive template func : 113364ms
        Recursive template struct : 2ms
        Compile-time array : 2ms
        Constexpr : 2ms 
        
    With optimizations (-O3):

        Normal : 21605ms
        Inline : 21522ms
        Recursive template func : 0ms
        Recursive template struct : 0ms
        Compile-time array : 0ms
        Constexpr : 0ms
