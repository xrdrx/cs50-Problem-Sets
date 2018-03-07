#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])

{

    //Arguments check!
    if (argc != 2)
    {
        printf("Wrong number of arguments!\n");
        return 1;
    }

    for (int j = 0, n = strlen(argv[1]); j < n; j++)
    {
        if (!isalpha(argv[1][j]))
        {
            j = n;
            printf("Not all chars are letters!\n");
            return 1;
        }

    }

    //Arg to string
    string sKeyString = argv[1];
    for (int i = 0, n = strlen(sKeyString); i < n; i++)
    {
        sKeyString[i] = toupper(sKeyString[i]);
    }

    //Promt for source text
    string sPlaintext = get_string("plaintext: ");



    //Arg string length
    int iKSL = strlen(sKeyString);

    printf("ciphertext: ");

    //Cipher
    int iLCounter = 0;

    for (int i = 0, n = strlen(sPlaintext); i < n; i++)
    {

        if (islower(sPlaintext[i]))
        {
            printf("%c", 97 + (sPlaintext[i] + sKeyString[(iLCounter % iKSL)] - 97 - 65) % 26);
            iLCounter++;
        }
        else if (isupper(sPlaintext[i]))
        {
            printf("%c", 65 + (sPlaintext[i] + sKeyString[(iLCounter % iKSL)] - 65 - 65) % 26);
            iLCounter++;
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