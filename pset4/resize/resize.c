// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    //remember scale
    int iScale = atoi(argv[1]);
    printf("Scale: %i\n", iScale);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    //source file parameters
    // printf("source bfSize, bfOffBits: %i, %i\n", bf.bfSize, bf.bfOffBits);
    // printf("source biSize, biWidth, biHeight, biSizeImage: %i, %i, %i, %i\n", bi.biSize, bi.biWidth, bi.biHeight, bi.biSizeImage);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines
    int OldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //Create new headers
    BITMAPFILEHEADER *bfBuffer;
    BITMAPFILEHEADER bfNew;
    bfBuffer = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER) * 1);
    *bfBuffer = bf;
    bfNew = (BITMAPFILEHEADER) * bfBuffer;
    free(bfBuffer);

    BITMAPINFOHEADER *biBuffer;
    BITMAPINFOHEADER biNew;
    biBuffer = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER) * 1);
    *biBuffer = bi;
    biNew = (BITMAPINFOHEADER) * biBuffer;
    free(biBuffer);

    //Calculate new header values
    biNew.biWidth = bi.biWidth * iScale;
    biNew.biHeight = bi.biHeight * iScale;
    int NewPadding = (4 - (biNew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    biNew.biSizeImage = ((sizeof(RGBTRIPLE) * biNew.biWidth) + NewPadding) * abs(biNew.biHeight);
    bfNew.bfSize = biNew.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // //out file params
    // printf("new bfSize, bfOffBits: %i, %i\n", bfNew.bfSize, bfNew.bfOffBits);
    // printf("new biSize, biWidth, biHeight, biSizeImage: %i, %i, %i, %i\n", biNew.biSize, biNew.biWidth, biNew.biHeight, biNew.biSizeImage);
    printf("OldPadding, NewPadding: %i, %i\n", OldPadding, NewPadding);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfNew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biNew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    // int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Counter for line rewinds
        int iLines = 1;

        //write iScale lines to outfile
        for (int iMult0 = 0; iMult0 < iScale; iMult0++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                printf("Pos: %li\n", ftell(inptr));
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple iScale times to outfile
                for (int iMult1 = 0; iMult1 < iScale; iMult1++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // skip over padding, if any
            fseek(inptr, OldPadding, SEEK_CUR);
            printf("NewPosAfterPadding: %li\n", ftell(inptr));

            // then add it back (to demonstrate how)
            for (int k = 0; k < NewPadding; k++)
            {
                fputc(0x00, outptr);
            }

            if (iScale > 1 && iLines < iScale)
            {
                fseek(inptr, - sizeof(RGBTRIPLE) * bi.biWidth - OldPadding, SEEK_CUR);
                printf("NewPos: %li\n", ftell(inptr));
                iLines++;
            }


        }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
