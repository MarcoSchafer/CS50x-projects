#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define JPG_SIZE 512

// Function prototype
bool jpg_start(uint8_t buffer[JPG_SIZE]);

int main(int argc, char *argv[])
{
    // Check for correct input (program name + input file)
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open file for reading
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        printf("");
        return 1;
    }

    uint8_t buffer[JPG_SIZE];       // temporary storage for each 512-byte block
    char filename[8];               // string to store generated JPEG filenames 
    int img_count = 0;              // counts how many JPEGS have been found
    FILE *img = NULL;               // pointer to the current JPEG file being written

    // Read blocks of 512 bytes until end-of-file (EOF)
    while (fread(buffer, 1, JPG_SIZE, card) == JPG_SIZE)
    {
        // If new JPEG header is detected
        if (jpg_start(buffer))
        {
            //If already writing a JPEG, close it before starting a new one
            if (img != NULL)
            {
                fclose(img);
            }

            // Create a new JPEG file with a sequential filename
            sprintf(filename, "%03i.jpg", img_count++);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Could not create JPEG %s\n");
                return 1;
            }
        }

        // If currently writing a JPEG, append the current block to it
        if (img != NULL)
        {
            fwrite(buffer, 1, JPG_SIZE, img);
        }
    }
    
    // Close the last jpeg if one was open
    if (img != NULL)
    {
        fclose(img);
    }

    // Close the file
    fclose (card);

    return 0;
}
// Function to check if given 512-byte block contains the start of a jpeg file
bool jpg_start(uint8_t buffer[JPG_SIZE])
{
    return (buffer[0] == 0xff &&
            buffer[1] == 0xd8 && 
            buffer[2] == 0xff && 
            (buffer[3] && 0xf0) == 0xe0);
}

