int reverse_int(int n)
{
    int result = 0;

    while (n > 0)
    {
        result = (n % 10) + result * 10;
        n /= 10;
    }

    return result;
}

int str_length(const char *str)
{
    int length = 0;

    while (*str != '\0')
    {
        length++;
        str++;
    }

    return length;
}

int get_char_at(int n, const char *str, int length)
{
    char c = '\0';

    int i = 0;
    while (n < length && c == '\0')
    {
        if (i == n)
            c = str[i];
        i++;
    }

    return c;
}

int power(int a, int b)
{
    while (b > 0)
    {
        a *= a;
        b--;
    }
    return a;
}

char *my_itoa_base(int n, char *s, const char *base)
{
    int baseLength = str_length(base);

    int strLength = 0;
    int a = n;
    while (a > 0)
    {
        strLength++;
        a /= baseLength;
    }

    int i = 0;
    while (n > 0)
    {
        s[strLength - i - 1] = base[n % baseLength];
        n /= baseLength;
        i++;
    }

    //s[0] = '\0';
    s[strLength] = '\0';

    return s;
}
