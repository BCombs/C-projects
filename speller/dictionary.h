/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Capacity for a trie
#define CAPACITY 27

// node for trie
typedef struct node
{
    // Flag to note it is the end of a valid word
    bool isWord;
    
    // Pointers to other nodes
    struct node* children[CAPACITY];
    
} node;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word);

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

/**
 * Frees each node in the trie
 */
bool freeTrie(node* trav);

#endif // DICTIONARY_H
