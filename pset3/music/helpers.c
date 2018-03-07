// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int iX = fraction[0] - '0';
    int iY = fraction[2] - '0';
    int iDuration = 8 * iX / iY;
    return iDuration;
}

//Calculates frequency (in Hz) of a note
int frequency(string note)
{
    double MultiN;
    double MultiNote;
    int iOctave;
    int iFreq;
    int iDiff;

    //Add multipliers for sharp and flat notes
    if (note[1] == '#')
    {
        MultiN = pow(2, 1.0 / 12.0);
        iOctave = note[2] - '0';
    }
    else if (note[1] == 'b')
    {
        MultiN = 1 / pow(2, 1.0 / 12.0);
        iOctave = note[2] - '0';
    }
    else
    {
        MultiN = 1;
        iOctave = note[1] - '0';
    }

    //Add multipliers for notes other than A
    switch (note[0])
    {
        case 'C':
            MultiNote = 1 / pow(2, 9.0 / 12.0);
            break;
        case 'D':
            MultiNote = 1 / pow(2, 7.0 / 12.0);
            break;
        case 'E':
            MultiNote = 1 / pow(2, 5.0 / 12.0);
            break;
        case 'F':
            MultiNote = 1 / pow(2, 4.0 / 12.0);
            break;
        case 'G':
            MultiNote = 1 / pow(2, 2.0 / 12.0);
            break;
        case 'A':
            MultiNote = 1;
            break;
        case 'B':
            MultiNote = pow(2, 2.0 / 12.0);
            break;
    }

    //Calculate diffence relative to 4th octave
    iDiff = iOctave - 4;

    //Calculate frequency
    iFreq = round(440 * ((float) pow(2, iDiff)) * MultiN * MultiNote);

    return iFreq;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //If length of the string is zero, than consider it a rest
    if (strlen(s) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
