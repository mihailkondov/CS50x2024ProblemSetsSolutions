#include <stdio.h>

int main(void)
{
    char *s = "HI!"; // this points to the first character in the array [4] 'H' 'I' '!' '\0'
    printf("%c", *s);
    printf("%c", *(s + 1));
    printf("%c", *(s + 2));
    printf("\n");

    printf("%c", s[0]);
    printf("%c", s[1]);
    printf("%c", s[2]);
    printf("\n");

    // *(s + 1) <=> s[1]

    char arr[4];
    arr[0] = 'H';
    arr[1] = 'I';
    arr[2] = '!';
    arr[3] = '\0';
    printf("%s\n", &arr[0]);

    // this doesn't compile:
    // printf("%s\n", &arr);
}
