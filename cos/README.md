# Cos

## How to use it

    * **make** or **make opt**
    * ./cos <loop_count>

    Computes <loop_count> times cos(45)

## Results

    ./cos 1000000

    Without optimizations:

        Normal : 235905ms
        Inline : 235717ms
        Recursive template func : 238374ms
        Recursive template struct : 1ms
        Compile-time array : 2ms
        Constexpr : 2ms

    With optimizations (-O3):

        Normal : 46491ms
        Inline : 48100ms
        Recursive template func : 0ms
        Recursive template struct : 0ms
        Compile-time array : 0ms
        Constexpr : 0ms
