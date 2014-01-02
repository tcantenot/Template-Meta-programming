# Factorial

## How to use it

    * **make** or **make opt**
    * ./factorial <loop_count>

    Computes <loop_count> times factorial 100.

## Results

    ./factorial 1000000

    (100! = 93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000)

    Without optimizations:

        Normal : 1109ms
        Inline : 1120ms
        Recursive template func : 1023ms
        Recursive template struct : 2ms
        Compile-time array : 2ms
        Constexpr : 2ms

    With optimizations (-O3):

        Normal : 244ms
        Inline : 244ms
        Recursive template func : 0ms
        Recursive template struct : 0ms
        Compile-time array : 0ms
        Constexpr : 0ms
