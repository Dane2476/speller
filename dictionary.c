// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"


typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int counter = 0;
node *hashTable[26];

int hashFunct(const char* key)
{
    int hash = toupper(key[0]) - 'A';
    return hash % 26;
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dictFile = fopen(dictionary, "r");
    if (dictFile == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(dictFile, "%s", word) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }
        else
        {
            counter++;
            int x = hashFunct(word);
            new_node->next = hashTable[x];
            hashTable[x] = new_node;
            strcpy(new_node->word, word);

        }
    }
    fclose(dictFile);
    return true;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int a = hashFunct(word);
    node *cursor = hashTable[a];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (counter == 0)
    {
        return 0;
    }
    else
    {
        return counter;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = hashTable[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        free(cursor);
    }
    return true;
}
