// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"

#define HASH 200003

//Declaring globas variables
node *hashtable[HASH]; //hashtable
FILE *dict; //dictionary file
int counter; //words in dictionary
char *tocheck;
int stop;
node *mempool;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    stop = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        tocheck[i] = tolower(word[i]);
        stop++;
    }
    tocheck[stop] = '\0';
    node *ptr = hashtable[(hash(tocheck) % HASH)];
    while (ptr != NULL)
    {
        if (strcmp(ptr->word, tocheck) == 0)
        {
            return true;
        }
        else
        {
            ptr = ptr->next;
        }
    }

    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //Dictionary word counter
    counter = 0;

    mempool = malloc(HASH * sizeof(node));
    node *nextfree = mempool;

    char *word = malloc((LENGTH + 1) * sizeof(char));

    while (fscanf(dict, "%s", word) != EOF)
    {
        //Calculating hash
        int k = hash(word) % HASH;

        //if node exists, make linked list
        if (hashtable[k])
        {
            node *new_node = nextfree++;
            if (new_node == NULL)
            {
                unload();
                return false;
            }
            strcpy(new_node->word, word);
            new_node->next = hashtable[k];
            hashtable[k] = new_node;
            counter++;
        }
        //else create new node
        else
        {
            hashtable[k] = nextfree++; //calloc(1, sizeof(node));
            if (hashtable[k] == NULL)
            {
                unload();
                return false;
            }
            strcpy(hashtable[k]->word, word);
            hashtable[k]->next = NULL;
            counter++;
        }
    }
    free(word);
    fclose(dict);
    tocheck = malloc((LENGTH + 1) * sizeof(char));
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
    // for (int i = 0; i < HASH; i++)
    // {
    //     node *ptr = hashtable[i]->next;
    //     while (ptr != NULL)
    //     {
    //         node *next = ptr->next;
    //         free(ptr);
    //         ptr = next;
    //     }
    // }
    free(mempool);
    free(tocheck);
    return true;
}

unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}
