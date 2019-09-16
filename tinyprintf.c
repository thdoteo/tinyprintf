#include <stdio.h>
#include <stdarg.h>

#include "buffer.h"
#include "tinyprintf.h"
#include "my_itoa_base.h"

/*
** Functions - Directives
*/

int is_char_directive(char c)
{
    return c == '%' || c == 'd' || c == 'u' || c == 's' || c == 'c'
        || c == 'o' || c == 'x';
}

void handle_character(char value, struct buffer *b)
{
    buffer_add(value, b);
}

void handle_string(char *value, struct buffer *b)
{
    if (value == NULL)
    {
        char nullMessage[] = "(null)";
        value = nullMessage;
    }

    while (*value != '\0')
    {
        buffer_add(*value, b);
        value++;
    }
}

void handle_signed_integer(int value, struct buffer *b)
{
    char s[12];
    my_itoa_base(value, s, "0123456789");
    handle_string(s, b);
}

void handle_unsigned_integer(unsigned value, struct buffer *b)
{
    char s[12];
    my_itoa_base(value, s, "0123456789");

    if (s[0] == '-')
        return;

    handle_string(s, b);
}

void handle_octal(unsigned value, struct buffer *b)
{
    char s[50];
    my_itoa_base(value, s, "01234567");

    if (s[0] == '-')
        return;

    handle_string(s, b);
}

void handle_hexadecimal(unsigned value, struct buffer *b)
{
    char s[50];
    my_itoa_base(value, s, "0123456789abcdef");

    if (s[0] == '-')
        return;

    handle_string(s, b);
}

void handle_directives(const char *format, struct buffer *b, va_list args)
{
    if (*format == '%')
        handle_character(*format, b);
    else if (*format == 'd')
        handle_signed_integer(va_arg(args, int), b);
    else if (*format == 'u')
        handle_unsigned_integer(va_arg(args, unsigned), b);
    else if (*format == 's')
        handle_string(va_arg(args, char*), b);
    else if (*format == 'c')
        handle_character(va_arg(args, int), b);
    else if (*format == 'o')
        handle_octal(va_arg(args, unsigned), b);
    else if (*format == 'x')
        handle_hexadecimal(va_arg(args, unsigned), b);
}

/*
** Function - tinyprintf
*/

int tinyprintf(const char *format, ...)
{
    struct buffer b;
    buffer_create(&b);

    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format != '%'
            && (*(format + 1) != '\0' || !is_char_directive(*(format + 1))))
        {
            handle_character(*format, &b);
            format++;
        }
        else
        {
            format++;
            handle_directives(format, &b, args);
            format++;
        }

        // Handle full buffer
        if (buffer_is_full(&b))
        {
            buffer_flush(&b);
        }
    }

    // Print characters remaining in the buffer
    if (b.index != 0)
    {
        buffer_flush(&b);
    }

    va_end(args);

    return b.numberOfCharacters;
}
