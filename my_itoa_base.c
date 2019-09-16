int get_digits_in_number(int n)
{
    int count = 0;

    while (n > 0)
    {
        n /= 10;
        count++;
    }

    return count;
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

char *my_itoa_base(int n, char *s, const char *base)
{
    int baseLength = str_length(base);

    int abs = (n < 0) ? -n : n;
    char *p = s + get_digits_in_number(abs);

    if (n >= 0)
    {
        p--;
    }

    while (p != s - 1)
    {
        *p = get_char_at((abs % baseLength), base, baseLength);
        p--;
        abs /= baseLength;
    }

    if (n < 0)
    {
        *s = '-';
    }

    return s;
}
