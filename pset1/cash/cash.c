#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{
    float fChange;
    int iChange;
    int i25Change;
    int i10Change;
    int i5Change;
    int i1Change;
    int iNumberCoins;

    //Promt for needed change
    do
    {
        fChange = get_float("Enter needed change: ");
    }
    while ( fChange < 0 || fChange > 23 );

    //Calculate cash in cents
    iChange = round(fChange * 100);
    //Calculate number of 25 cents coins
    i25Change = floor(iChange / 25);
    //Calculate number of 10 cents coins
    i10Change = floor((iChange - (i25Change * 25)) / 10);
    //Calculate number of 5 cents coins
    i5Change = floor((iChange - (i25Change * 25 + i10Change * 10)) / 5);
    //Calculate number of 1 cent coins
    i1Change = iChange - i25Change * 25 - i10Change * 10 - i5Change * 5;
    //Calculate total number of coins
    iNumberCoins = i25Change + i10Change + i5Change + i1Change;

    printf("%i\n", iNumberCoins);

}