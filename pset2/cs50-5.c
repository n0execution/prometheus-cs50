#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>



//encrypts inputted text by caesar cipher
int main(int argc, string argv[])
{
    //checks the number of arguments
    if (argc == 1 || argc > 2)
    {
        printf("Error. Something wrong!\n");
        return 1;
    }
    //converts string to int
    int k = atoi(argv[1]);
    
    
    //works with inputted text
    string text = GetString();
    int n = strlen(text);
    char new_text[n];
    for (int i = 0; i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
            new_text[i] = 65 + (text[i] - 65 + k) % 26;
        else if(text[i] >= 'a' && text[i] <= 'z')
            new_text[i] = 97 + (text[i] - 97 + k) % 26;
        else
            new_text[i] = text[i];
    }
    
    //prints new text
    for (int i = 0; i < n; i++)
        printf("%c", new_text[i]);
    printf("\n");
    
    return 0;
}
