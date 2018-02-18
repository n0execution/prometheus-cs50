#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

//prints initials of inputted name
int main(void)
{
    printf("Enter your name, please: ");
    string name = GetString();
    printf("Your initials: %c", toupper(name[0]));
    if(name != NULL)
        for (int i = 0, n = strlen(name); i < n; i++)
        {
            char c = name[i];
            if (c == ' ')
                printf("%c", toupper(name[i + 1]));
        }
    printf("\n");
    
    return 0;
}

