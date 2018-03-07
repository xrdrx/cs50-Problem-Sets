#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>

int main(void)

{
//    string sAlphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string sAlphabet = "ROFL";
//    string s = crypt("ROFL", "50");
    string sHash = 50JGnXUgaafgc;
    string sSalt = sHash[0] & sHash[1];
    printf("%s", sSalt);
}