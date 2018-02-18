#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//encrypts inputted text by caesar vigenere
int main(int argc, string argv[])
{
    //checks the number of arguments
    if (argc == 1 || argc > 2)
    {
        printf("Error. Something wrong!\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if(isalpha(argv[1][i]) == 0)
        {
            printf("Error. Something wrong!\n");
            return 1;
        }
    }
    
    //prepares some variables to work
    string text = GetString();
    int size1 = strlen(text);
    int size2 = strlen(argv[1]);
    string key = argv[1];
    int k;
    
    
    //works with inputted text
    for (int i = 0, j = 0; i < size1; i++, j++)
    {
        if (j == size2)
            j = 0;
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            if (key[j] >= 'A' && key[j] <= 'Z')
                k = key[j] - 65;
            else
                k = key[j] - 97;
            text[i] = 65 + (text[i] - 65 + k) % 26;
        }
        else if(text[i] >= 'a' && text[i] <= 'z')
        {
            if (key[j] >= 'A' && key[j] <= 'Z')
                k = key[j] - 65;
            else
                k = key[j] - 97;
            text[i] = 97 + (text[i] - 97 + k) % 26;
        }
        else
        {
            text[i] = text[i];
            --j;
        }
    }
    
    //prints new text
    for (int i = 0; i < size1; i++)
        printf("%c", text[i]);
    
    return 0;
}
