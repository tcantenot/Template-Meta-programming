template <int Begin, int End>
struct Loop
{
    static void Do()
    {
        //DoSth();
        Loop<Begin + 1, End>::Do();
    }
};

template <int N>
struct Loop<N, N>
{
    static void Do() { }
};
