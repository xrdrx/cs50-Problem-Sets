// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "dictionary.h"


//Declaring globas variables
node *root; //trie root
node *Start; //changing pointer
FILE *dict; //dictionary file
int counter; //words in dictionary

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    Start = root;

    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] == '\'')
        {
            if (Start->children[(word[i]) - 13])
            {
                Start = Start->children[(word[i]) - 13];
            }
            else
            {
                return false;
            }
        }
        else if (Start->children[tolower(word[i]) - 97])
        {
            Start = Start->children[tolower(word[i]) - 97];
        }
        else
        {
            return false;
        }
    }

    return Start->is_word;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    int index = 0;
    counter = 0;

    //allocating memory for root
    root = calloc(1, sizeof(node));
    Start = root;

    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        if (isalpha(c))
        {
            index++;
            //check if node exist
            if (Start->children[c - 97] == NULL)
            {
                Start->children[c - 97] = calloc(1, sizeof(node));
                Start = Start->children[c - 97];
            }
            else
            {
                Start = Start->children[c - 97];
            }
        }
        else if (c == '\'' && index > 0)
        {
            index++;
            if (Start->children[c - 13] == NULL)
            {
                Start->children[c - 13] = calloc(1, sizeof(node));
                Start = Start->children[c - 13];
            }
            else
            {
                Start = Start->children[c - 13];
            }
        }
        else if (index > 0) //reached end of word
        {
            counter++;
            Start->is_word = true;
//            printf("Word exists\n");
            Start = root;
        }

    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    free_memory(root);
    fclose(dict);
    return true;
}

//frees trie memory in recursion
void free_memory(struct node *p)
{
    for (int i = 0; i < 27; ++i)
    {
        if (p->children[i])
        {
            free_memory (p->children[i]);
        }
    }
    free (p);
}