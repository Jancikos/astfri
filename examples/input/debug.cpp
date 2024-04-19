
int simpleAddition (int a, int b = 0)
{
    int c;

    c     = 2;

    c     = a + 1;

    int d = 4;
    int e = 4 + d;

    d += 5;

    return a + b;
}

int simpliestAddition2 (int a, int b)
{
    int repMultiplier = 1;

    if (a < 0)
    {
        repMultiplier = -1;
    }

    int repCount = 0;
    while (a + repCount < 0)
    {
        repCount = repMultiplier + 1;
    }

    for (int i = 0; i < 10; i = i + 1)
    {
        repCount = repMultiplier + 1;
    }

    return simpliestAddition2(a, b);
}

int simpliestAddition (int o)
{
    return o + o;
}

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
        sum = sum + i;
    }

    return sum;
}
