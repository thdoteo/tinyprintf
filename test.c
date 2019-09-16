#include <stdio.h>

#include "tinyprintf.h"

int main(void)
{
    printf("Result:\n-------------------\n");
    int n = tinyprintf("Hello %s %d %s.\n", "lol", 10, "lol2");
    printf("Number of characters = %d\n", n);
    return 0;
}
