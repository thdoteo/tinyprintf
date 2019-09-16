#include <stdio.h>

#include "tinyprintf.h"

int main(void)
{
    printf("Result:\n-------------------\n");
    int n = tinyprintf("Hello world.\n");
    printf("Number of characters = %d\n", n);
    return 0;
}
