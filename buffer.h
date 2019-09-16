#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_MAX_SIZE 256

struct buffer {
    char buffer[BUFFER_MAX_SIZE];
    int index;
    int numberOfCharacters;
};

void buffer_create(struct buffer *b);
void buffer_flush(struct buffer *b);
int buffer_is_full(struct buffer *b);
void buffer_add(char c, struct buffer *b);

#endif /* BUFFER_H */
