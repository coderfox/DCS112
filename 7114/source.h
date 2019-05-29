template <typename T>
T maxValue(const T value1, const T value2)
{
    return value1 > value2 ? value1 : value2;
}

char normalize(const char c)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    else
        return c;
}

char maxValue(const char v1, const char v2)
{
    return normalize(v1) >= normalize(v2) ? v1 : v2;
}