#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "helpers.h"        // include helper header file

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "bgrs";
    char filter = 0;

    // Parse command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, filters)) != -1)
    {
        switch (opt)
        {
            case 'b':
            case 'g':
            case 'r':
            case 's':
                filter = opt;
                break;
            case '?':
                printf("Invalid filter\n");
                return 1;
        }
    }

    // Ensure only one filter
    if (filter == 0)
    {
        printf("usage: ./filter [flag] infile outfile\n");
        return 2;
    }
    
    // Ensure proper usage
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Assign filenames
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s\n", infile);
        return 4;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s\n", outfile);
        return 5;
    } 

    // Read infile BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || 
        bf.bfOffBits != 54 || 
        bi.biSize != 40 ||
        bi.biBitCount != 24 ||
        bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format\n");
        return 6;
    }

    // Get image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image as 2D array
    RGBTRIPLE (*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Read pixels into memory
    for (int i = 0; i < height; i++)
    {
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);       
        fseek(inptr, padding, SEEK_CUR);                        
    }

    // Apply filter
    switch (filter)
    {
        // Blur
        case 'b':
        blur(height, width, image);
        break;

        // Greyscale
        case 'g':
        grayscale(height, width, image);
        break;

        // Reflection
        case 'r':
        reflect(height, width, image);
        break;

        // Sepia
        case 's':
        sepia(height, width, image);
        break;
    }

    // Write outfile headers
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Add padding
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    
    return 0;    
}