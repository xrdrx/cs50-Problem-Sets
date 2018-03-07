#include <stdio.h>
#include <cs50.h>

int main(void)

{
    int nPHeight;

    //Promt for pyramin height
    do
    {
        nPHeight = get_int("Enter positive number no greater than 23: ");
    }
    while ( nPHeight < 0 || nPHeight > 23 );

    for (int i = 0; i < nPHeight; i++)
    {
        //For each line draw Pyramin height minus line number minus 1 spaces
        for (int j = nPHeight - i - 1; j > 0; j--)
        {
            printf(" ");
        }
        //For each line draw line number plus 2 hash
        for (int k = 0; k < i + 2; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}