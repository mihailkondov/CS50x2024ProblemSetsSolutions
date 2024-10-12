// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]); // atof = ascii to float

    // TODO: Copy header from input file to output file
    BYTE buffer[HEADER_SIZE];
    fread(&buffer, sizeof(BYTE), HEADER_SIZE, input); // stores into buffer 1 byte sized chunks,
                                                      // 44 (HEADER_SIZE) at a time from the file
                                                      // with the address input
    fwrite(&buffer, sizeof(BYTE), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer2;
    while (fread(&buffer2, sizeof(uint16_t), 1, input))
    {
        float result = buffer2 * factor;
        buffer2 = (int16_t) result;
        fwrite(&buffer2, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
