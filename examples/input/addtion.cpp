
int simpliestAddition2(int a, int b)
{
    int repMultiplier = 1;

    if (a < 0) {
        repMultiplier = -1;
    }

    return a + b;
}

int simpleAddition(int a, int b=0)
{
    int c;
    c = a + 1;

    int d = 4;
    int e = 4 + d;

    d = 5;

    return simpliestAddition2(a, b);
}

int simpliestAddition(int o)
{
    return o + o;
}
