#include <stdio.h>
#include <stdarg.h>

#include "tinyprintf.h"
#include "my_itoa_base.h"

/*
** Functions - Buffer
*/

void buffer_create(struct buffer *b)
{
    for (int i = 0; i < BUFFER_MAX_SIZE; i++)
    {
        b->buffer[i] = 0;
    }
    b->index = 0;
    b->numberOfCharacters = 0;
}

void buffer_flush(struct buffer *b)
{
    // Print
    b->buffer[b->index] = '\0';
    fputs(b->buffer, stdout);

    // Reset
    for (int i = 0; i < BUFFER_MAX_SIZE; i++)
    {
        b->buffer[i] = 0;
    }
    b->numberOfCharacters += b->index;
    b->index = 0;
}

int buffer_is_full(struct buffer *b)
{
    return b->index == BUFFER_MAX_SIZE - 1;
}

void buffer_add(char c, struct buffer *b)
{
    if (buffer_is_full(b))
    {
        buffer_flush(b);
    }

    b->buffer[b->index] = c;
    b->index = b->index + 1;
}

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
    my_itoa_base(value, s, "0123456789ABCDEF");

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
