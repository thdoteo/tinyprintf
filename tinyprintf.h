#ifndef TINYPRINTF_H
#define TINYPRINTF_H

#define BUFFER_MAX_SIZE 256

struct buffer {
    char buffer[BUFFER_MAX_SIZE];
    int index;
    int numberOfCharacters;
};

int tinyprintf(const char *format, ...);

#endif /* TINYPRINTF_H */
