// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26; // 26 letters in the english alphabet

// Hash table
node *table[N];
int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    bool found = false;
    for (node *tmp = table[hash(word)]; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            found = true;
            break; // no need to look further
        }
    }
    
    return found;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // return toupper(word[0]) - 'A';
    return tolower(word[0]) - 97; // a in ascii = 97. a/A => 0, b/B => 1 ... until z/Z => 25
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // store dictionary in a hash table (array of linked lists)
    FILE *dict_file = fopen(dictionary, "r");
    if (dict_file == NULL)
    {
        fclose(dict_file);
        return false;
    }

    // char *word = malloc(sizeof(LENGTH));
    char word[LENGTH];
    while (fscanf(dict_file, "%s", word) != EOF)
    {
        // printf("> %s\n", word);
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            free(new_node);
            return false;
        }
        strcpy(new_node->word, word); // add word to new node
        new_node->next = NULL; // initially, set new node's next value to NULL

        unsigned int h = hash(word); // get index where to insert new node into table

        // insert node into table
        if (table[h] == NULL) // no linked list yet in table index of that word's hash
        {
            table[h] = new_node;
        }
        else // list exists at that index, insert new word at the beginning of the linked list 
        {
            new_node->next = table[h];
            table[h] = new_node;
        }

        words += 1;
    }

    fclose(dict_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next; // find 2nd node
            free(table[i]); // free first node
            table[i] = tmp; // assign list node 2, repeat cycle
        }
    }

    return true;
}
