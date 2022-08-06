float random(float Min, float Max)
{
    return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}

float bound(float input, float Min, float Max)
{
    float result;
    if (input >= Max)
        result = Max;
    else if (input <= Min)
        result = Min;
    else
        result = input;

    return result;
}

float pythagoras(float a, float b)
{
    return sqrt(a * a + b * b);
}

