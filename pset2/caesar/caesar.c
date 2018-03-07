#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])

{
    //Number of arguments check!
    if (argc != 2)
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }

    //Convert string to int
    int iKey = atoi(argv[1]);

    //Promt for source text
    string sPlaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    //Cipher
    for (int i = 0, n = strlen(sPlaintext); i < n; i++)
    {
        if (islower(sPlaintext[i]))
        {
            printf("%c", 97 + (sPlaintext[i] + iKey - 97) % 26);
        }
        else if (isupper(sPlaintext[i]))
        {
            printf("%c", 65 + (sPlaintext[i] + iKey - 65) % 26);
        }
        else
        {
            printf("%c", sPlaintext[i]);
        }

    }

    printf("\n");

    //Exit
    return 0;
}