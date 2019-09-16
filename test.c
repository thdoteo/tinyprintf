#include <stdio.h>

#include "tinyprintf.h"

int main(void)
{
    printf("Example 5.1\n");
    int n = tinyprintf("%s [%d] %s", "Hello", 42, "world!");
    printf("\nNumber of characters = %d\n\n", n);

    printf("Example 5.2\n");
    n = tinyprintf("%s [%x] %s", "Hello", 42, "world!");
    printf("\nNumber of characters = %d\n\n", n);

    printf("Example 5.3\n");
    n = tinyprintf("%%s", "in your head");
    printf("\nNumber of characters = %d\n\n", n);

    printf("Example 5.4\n");
    n = tinyprintf("Good morning ACU! %t Tinyprintf is cool", 12);
    printf("\nNumber of characters = %d\n\n", n);

    printf("Example 5.5\n");
    n = tinyprintf("%c%c is %s... %d too.", '4', '2', "the answer", '*');
    printf("\nNumber of characters = %d\n\n", n);


    return 0;
}
