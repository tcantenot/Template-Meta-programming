# Power

## How to use it

    * **make** or **make opt**
    * ./pow <loop_count>

    Computes <loop_count> times 2^100.

## Results

    ./pow 1000000

    (2^100 = 1267650600228229401496703205376)

    Without optimizations:

        Normal : 1228ms
        Inline : 1228ms
        Recursive template func : 1295ms
        Recursive template struct : 2ms
        Compile-time array : 2ms
        Constexpr : 2ms

    With optimizations (-O3):

        Normal : 224ms
        Inline : 231ms
        Recursive template func : 0ms
        Recursive template struct : 0ms
        Compile-time array : 0ms
        Constexpr : 0ms
