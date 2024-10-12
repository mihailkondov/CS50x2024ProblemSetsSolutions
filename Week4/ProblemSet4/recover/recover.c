#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("usage: ./recover filename\n");
        return 1;
    }
    // Open the memory card
    FILE *recover = fopen("card.raw", "r");
    if (recover == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    // While there's still data left to read from the memory card
    BYTE buffer[512];
    int n = 0;
    FILE *jpg = NULL;
    char new_file_name[8];
    while (fread(&buffer, 1, 512, recover)) // reads card.raw
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // close previous file
            if (jpg != NULL)
            {
                fclose(jpg);
            }

            printf("JPEG %i found\n", n);

            // prepare name
            sprintf(new_file_name, "%03d.jpg", n);
            n++;

            // create new file
            jpg = fopen(new_file_name, "w");
            if (jpg == NULL)
            {
                printf("Unable to create a file\n");
                return 1;
            }
        }

        if (jpg != NULL)
        {
            fwrite(&buffer, 1, 512, jpg);
        }
    }
    if (jpg != NULL)
    {
        fclose(jpg);
    }
    fclose(recover);
}
