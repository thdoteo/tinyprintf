#include <stdio.h>
#include <stdarg.h>

#include "tinyprintf.h"
#include "my_itoa_base.h"

#define BUFFER_SIZE 512

/*
** Functions - Buffer
*/

int length_buffer(char *buffer)
{
    int length = 0;
    while (*buffer != '\0')
    {
        length++;
        buffer++;
    }
    return length;
}

int clear_and_print_buffer(char buffer[], int *bufferIndex)
{
    buffer[*bufferIndex] = '\0';
    int length = length_buffer(buffer);
    fputs(buffer, stdout);
    *bufferIndex = 0;
    return length;
}

void add_char_buffer(char c, char buffer[], int *bufferIndex)
{
    // Handle full buffer
    if (*bufferIndex == BUFFER_SIZE - 1)
    {
        clear_and_print_buffer(buffer, bufferIndex);
    }

    buffer[*bufferIndex] = c;
    *bufferIndex = *bufferIndex + 1;
}

/*
** Functions - Directives
*/

int is_directive(char c)
{
    return c == '%' || c == 'd' || c == 'u' || c == 's' || c == 'c'
        || c == 'o' || c == 'x';
}

void handle_character(
    char value,
    const char **format,
    char buffer[],
    int *index
)
{
    add_char_buffer(value, buffer, index);
    *format = *format + 1;
}

void handle_string(
    char *value,
    const char **format,
    char buffer[],
    int *index
)
{
    while (*value != '\0')
    {
        add_char_buffer(*value, buffer, index);
        value++;
    }
    *format = *format + 1;
}

void handle_signed_integer(
    int value,
    const char **format,
    char buffer[],
    int *index
)
{
    char s[12];
    my_itoa_base(value, s, "0123456789");
    handle_string(s, format, buffer, index);
}

void handle_unsigned_integer(
    int value,
    const char **format,
    char buffer[],
    int *index
)
{
    
}

void handle_octal(
    int value,
    const char **format,
    char buffer[],
    int *index
)
{
    
}

void handle_hexadecimal(
    int value,
    const char **format,
    char buffer[],
    int *index
)
{
    
}

void handle_directives(
    const char **format,
    char buffer[],
    int *index,
    va_list args
)
{
    *format = *format + 1;

    if (**format == '%')
        handle_character(**format, format, buffer, index);
    else if (**format == 'd')
        handle_signed_integer(va_arg(args, int), format, buffer, index);
    else if (**format == 'u')
        handle_unsigned_integer(va_arg(args, unsigned), format, buffer, index);
    else if (**format == 's')
        handle_string(va_arg(args, char*), format, buffer, index);
    else if (**format == 'c')
        handle_character(va_arg(args, int) + '0', format, buffer, index);
    else if (**format == 'o')
        handle_octal(va_arg(args, unsigned), format, buffer, index);
    else if (**format == 'x')
        handle_hexadecimal(va_arg(args, unsigned), format, buffer, index);
}

/*
** Function - tinyprintf
*/

int tinyprintf(const char *format, ...)
{
    int numberOfCharacters = 0;
    int bufferIndex = 0;
    char buffer[BUFFER_SIZE];

    va_list args;
    va_start(args, format);

    while (*format != '\0')
    {
        if (*format != '%'
            && (*(format + 1) != '\0' || !is_directive(*(format + 1))))
        {
            handle_character(*format, &format, buffer, &bufferIndex);
        }
        else
        {
            handle_directives(&format, buffer, &bufferIndex, args);
        }

        // Handle full buffer
        if (bufferIndex == BUFFER_SIZE - 1)
        {
            numberOfCharacters += clear_and_print_buffer(buffer, &bufferIndex);
        }
    }

    // Print characters remaining in the buffer
    if (bufferIndex != 0)
    {
        numberOfCharacters += clear_and_print_buffer(buffer, &bufferIndex);
    }

    va_end(args);

    return numberOfCharacters;
}
