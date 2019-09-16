#include <stdio.h>

#include "tinyprintf.h"

int main(void)
{
    printf("Result:\n-------------------\n");
    int n = tinyprintf("Hello %s %d %o %x --- %s (%c).\n", "lol", 10, 10, 40, "test", 'r');
    printf("Number of characters = %d\n", n);
    return 0;
}
