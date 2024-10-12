#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    char c = 'A';

    printf("%s\n", s);
    printf("%c\n", c);
    printf("%s\n", &c); // this doesn't have a termination character next to it,
                        // so it prints out nonsense until eight consecutive
                        //  0-bits are encountered.

    *(&c + 1) = '\0';   // this alters memory that may not belong to the program
    printf("%s\n", &c); // but if nothing crashes it terminates the string.
}
