#include <stdio.h>

#include "buffer.h"

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
    b->index++;
}
