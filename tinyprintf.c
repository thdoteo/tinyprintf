#include <stdio.h>
#include <stdarg.h>

#define BUFFER_SIZE 2048

/*
** Functions - Buffer
*/

int clear_buffer(char buffer[], int bufferIndex)
{
    buffer[bufferIndex] = '\0';
    return 0;
}

void print_buffer(char buffer[])
{
    fputs(buffer, stdout);
}

/*
** Functions - Directives
*/

void handle_default(

)
{

}

void handle_signed_integer(
    int n,
    const char *format,
    char buffer[],
    int *bufferIndex
)
{
    int n = 0;
    
}

void handle_directives(
    const char *format,
    char buffer[],
    int *bufferIndex,
    va_list args
)
{
    format++;

    if (*format == '%')
        handle_default('%', format, buffer, &bufferIndex);
    else if (*format == 'd')
        handle_signed_integer(va_arg(args, int), format, buffer, &bufferIndex);
    else if (*format == 'u')
        handle_unsigned_integer(va_arg(args, unsigned), format, buffer, &bufferIndex);

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
        if (*format != '%' && !is_directive(*(format + 1)))
        {
            handle_default(format, buffer, &bufferIndex, args);
        }
        else
        {
            handle_directives(format, buffer, &bufferIndex, args);
        }

        // Handle full buffer
        if (bufferIndex == BUFFER_SIZE - 1)
        {
            print_buffer(buffer);
            bufferIndex = clear_buffer(buffer, bufferIndex);
        }
    }

    // Print characters remaining in the buffer
    if (bufferIndex != 0)
    {
        print_buffer(buffer);
        bufferIndex = clear_buffer(buffer, bufferIndex);
    }

    va_end(args);

    return numberOfCharacters;
}
