// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

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

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    // 1 Byte declared for buffer
    typedef uint8_t one_byte;

    // Buffer: Pointer to the buffer where data will be stored. A buffer is a region of memory used to temporarily store data
    one_byte buffer[HEADER_SIZE];
    // Read the header
    fread(buffer, sizeof(one_byte), HEADER_SIZE, input);
    // Write the header
    fwrite(buffer, sizeof(one_byte), HEADER_SIZE, output);

    printf("Data read from file: %s \n", buffer);
    // TODO: Read samples from input file and write updated data to output file
    int16_t sampleBuffer;
    // Use &buffer as an argument to fread or fwrite to read into or write from the buffer. (Recall that the & operator is used to get the address of the variable.)
    // On success, fread() and fwrite() return the number of items read or written. This number equals the number of bytes transferred only when size is 1. If an error occurs, or the end of the file is reached, the return value is a short item count (or zero).
    while (fread(&sampleBuffer, sizeof(sampleBuffer), 1, input) == 1)
    {
        // change the factor
        sampleBuffer = sampleBuffer * factor;
        // write to output file
        fwrite(&sampleBuffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
