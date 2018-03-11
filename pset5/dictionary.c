/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"
#define SIZE 65536

int words;

//determine struct of linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node* next;
}
node;



int hash( char *word)
{
    int hash = 5381;

    for (int i = 0; i < strlen(word); i++)
        hash = ((hash << 5) + hash) + word[i]; /* hash * 33 + c */

    return hash % SIZE;
}

node* hashtable[SIZE];




/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{

    int len = strlen(word);
    char *new_word = malloc(len+1);
    
    //copy the characters and make them lower case
    for (int i = 0; i < len; i++)
        new_word[i] = tolower(word[i]);
    
    //add the end of string character
    new_word[len] = '\0';

    //  hash the word
    int index = hash_function(new_word);

    // check the table for a node at that index
    node* temp = hashtable[index];
    if (temp)
    {
        // point a cursor node to the head node
        node* cursor = temp;

        // loop through the nodes while a next pointer isn't null
        while (cursor->next != NULL)
        {
            if (strcmp(new_word, cursor->word) == 0)
                return true;

            cursor = cursor->next;
        }

        if (strcmp(new_word, cursor->word) == 0)
    		return true;

        cursor = cursor->next;
    }
    return false;
}





/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    //open our dictionary
    FILE* fp = fopen(dictionary, "r");
    
    if (fp == NULL)
    {
        printf("Could not open the file!");
        return false;
    }
    
    //create a buffer to store each word in it
    char buffer[LENGTH + 2];
    words = 0;
    
    //loop through the dictionary
    while (fgets(buffer, sizeof(buffer), fp))
    {
        //change '\n' to '\0'
        buffer[strlen(buffer)- 1] = '\0';
        
        //create a temporary node
        node* temp = malloc(sizeof(node));
        
        
        //copy content of buffer to temp->word
        strncpy(temp->word, buffer, LENGTH + 1);
        temp->next = NULL;
    
        //hash the word
        unsigned int index = hash_function(buffer);
        
        
        //if  the hashtable has no value at that index 
        if (hashtable[index] == NULL)
            hashtable[index] = temp;
        
        else
        {
            //move cursor node to the head of linked list hashtable[index]
            node* cursor = hashtable[index];
            
            //loop through the list until cursor->next is not NULL
            while (cursor->next != NULL)
            {
                cursor = cursor->next;
            }
            
            
            //append the word to the end of a list
            cursor->next = temp;
        }
        
        words++;
    }
    //close the opened file
    fclose(fp);
    
    return true;
}





/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return words;
}





/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // for each element in the hashtable
    for (int i = 0; i < SIZE; i++)
    {
        // check the table for a node at that index
        node* cursor = hashtable[i];
        if (cursor)
        {
            // create a temporary node to save the position of the next node
            node* temp = cursor->next;

            // free the current node
            free(cursor);

            // move the cursor to the next node
            cursor = temp;
        }
    }
    return true;
}
