#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // Check number of arguments:
    if(argc!=3)
    {
        printf("Usage: ./cp srcfile dstfile\n");
        return 1;
    }

    // open source file
    FILE *src = fopen(argv[1], "rb");
    if (src == NULL)
    {
        printf("Unable to open file %s\n", argv[1]);
        return 3;
    }

    // initialize destination file
    FILE *dst = fopen(argv[2], "wb");
    if (dst == NULL)
    {
        printf("Unable to create file %s\n", argv[2]);
        return 4;
    }

    // create a buffer
    BYTE *buffer = malloc(sizeof(BYTE));
    if (buffer == NULL)
    {
        printf("Out of memory\n");
        return 2;
    }

    while(fread(buffer, sizeof(BYTE), 1, src))
    {
        fwrite(buffer, sizeof(BYTE), 1, dst);
    }

    free(buffer);

    if (dst != NULL)
    {
        fclose(dst);
    }

    if (src != NULL)
    {
        fclose(src);
    }
}
