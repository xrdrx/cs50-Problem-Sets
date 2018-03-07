#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //buffer for 512 bytes chunks
    unsigned char buffer[512];

    //test for end of file
    int iEnd = 512;

    //file counter
    int iFiles = 0;

    //found jpeg?
    int iFound = 0;

    //open file for writing
    char filename[10];
    sprintf(filename, "%03i.jpg", iFiles);
    FILE *outptr = fopen(filename, "w");

    do
    {
        fread(&buffer, 1, 512, inptr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            fwrite(&buffer, sizeof(buffer), 1, outptr);
            iFound = 1;
        }
    }
    while (iFound == 0);

    do
    {
        iEnd = fread(&buffer, 1, 512, inptr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            iFiles++;
            fclose(outptr);
            sprintf(filename, "%03i.jpg", iFiles);
            outptr = fopen(filename, "w");
        }
        if (iEnd == 512)
        {
            fwrite(&buffer, sizeof(buffer), 1, outptr);
        }

    }
    while (iEnd == 512);
}
