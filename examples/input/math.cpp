int fibonacci (int x)
{
    if (x == 0)
    {
        return 0;
    }

    if (x == 1)
    {
        return 1;
    }

    return fibonacci(x - 1) + fibonacci(x - 2);
}

int sumSequence (int a, int b)
{
    int sum = 0;

    for (int i = a; i < b; i = i + 1)
    {
        // sum = sum + i;
        sum += i;
    }

    return sum;
}
