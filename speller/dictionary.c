/**
 * Implements a dictionary's functionality.
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// The root of the trie
node* root;
node* trav;

// How many words are in the dictionary
int wordCount = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // Point to to root node to begin
    trav = root;
    
    // Counter for position in word and trie
    int i = 0;
    int index = 0;
    
    // While we are not at the end of the word
    while(word[i] != '\0')
    {
        if(word[i] == '\'')
        {
            index = 26;
        }
        else
        {
            // Determine its position in the trie
            index = tolower(word[i]) - 'a';
        }
        
        // If that node doesn't exist, the word is misspelled
        if(trav->children[index] == NULL)
        {
            return false;
        }
        
        // Move to the next node
        trav = trav->children[index];
        
        // Move to the next letter
        i++;
    }
    
    // We reached the end of the word, make sure it is valid
    if(trav->isWord)
    {
        return true;
    }
    
    // It was not a valid word
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // Create a root node at point root at it
    root = calloc(1, sizeof(node));
    
    // Check for calloc failure
    if(root == NULL)
    {
        fprintf(stderr, "Error allocating memory.\n");
        unload();
        return 1;
    }
    
    // Point trav to the root node
    trav = root;
    
    //Open the dictionary
    FILE* fp = fopen(dictionary, "r");
    if(fp == NULL)
    {
        // Couldn't open dictionary to load
        return false;
    }
    
    // Create a buffer to store the current word in
    char word[LENGTH + 1];
    int index = 0;
    
    while(fscanf(fp, "%s", word) != EOF)
    {
        // Iterate through the word
        for(int i = 0, length = strlen(word); i < length; i++)
        {
            if(word[i] == '\'')
            {
                index = 26;
            }
            else
            {
                index = (word[i] - 'a');
            }
            
            // If the element is NULL calloc a new node at that element and move to it
            if(trav->children[index] == NULL)
            {
                trav->children[index] = calloc(1, sizeof(node));
                
                // Check for failure
                if(trav->children[index] == NULL)
                {
                    // Couldn't allocate memory. Dictionary load failed.
                    return false;
                }
            }
            
            // Move to the next node
            trav = trav->children[index];
        }
        
        // Flag the node as the end of a valid word
        trav->isWord = true;
        wordCount++;
        
        // Move back to the root node to prepare for the next word
        trav = root;
    }
    
    // Close the dictionary
    fclose(fp);

    // We successfully loaded the library
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordCount;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // Make sure we are on the root node
    trav = root;
    
    if(freeTrie(trav))
    {
        return true;
    }
    
    return false;
}

// Frees each node in the trie
bool freeTrie(node* trav)
{
    if(trav == NULL)
        return false;
    
    for(int i = 0; i < CAPACITY; i++)
        freeTrie(trav->children[i]);
    
    free(trav);
    return true;
}
