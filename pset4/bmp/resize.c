/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    

    // remember filenames
    int n = atoi(argv[1]);
    
    if (n <= 0 && n > 100)
    {
        printf("Error!");
        return 2;
    }
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
   
    int old_width, old_height, old_size_img, old_size;
    
    old_width = bi.biWidth;
    old_height = abs(bi.biHeight);
    old_size_img = bi.biSizeImage;
    old_size = bf.bfSize;
    
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    int old_padding =  (4 - (old_width * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    RGBTRIPLE* str = malloc(bi.biWidth * sizeof(RGBTRIPLE));
    
    
 
    // iterate over infile's scanlines
    for (int i = 0; i < old_height; i++)
    {
    
        int index = 0;
        for(int j = 0; j < old_width; j++)
        {
            RGBTRIPLE ref;
            fread(&ref, sizeof(RGBTRIPLE), 1, inptr);
            for(int time = 0; time < n; time++)
            {
                str[index] = ref;
                index++;
            }
        }
        
        fseek(inptr, old_padding, SEEK_CUR);
        
        for(int l = 0; l < n; l++)
        {
            fwrite(str, bi.biWidth * sizeof(RGBTRIPLE), 1, outptr);
            for(int k = 0; k < padding; k++)
            {
              fputc(0x00, outptr);
            }
        }
    }

    free(str);
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
