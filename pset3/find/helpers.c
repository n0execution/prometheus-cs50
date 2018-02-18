/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    //returns false if n is negative
    if (n < 0)
        return false;
        
    // TODO: implement a binary searching algorithm
    int min = 0, max = n - 1, temp;
    while (n > 0)
    { 
        temp = min + (max - min) / 2;
        if (values[temp] == value)
            return true;
        
        else if (values[temp] > value)
        {
            max = temp - 1;
        }
        
        else if (values[temp] < value)
        {
            min = temp + 1;
        }
        n /= 2;
    }
            
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    
    
    //here I realize selection sorting algorithm
    int temp;
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (values[j] < values[min])
                min = j;
        }
        temp = values[i];
        values[i] = values[min];
        values[min] = temp;
    }
}

