#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    //user enters height until it is not more than 23 and more than 0
    do
    {
        printf("Enter the height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0);
    
    //draws a half of pyramide
    for (int i = 1; i < height + 1; i++)
    {
        for (int n = 0; n < height - i; n++)
            printf(" ");
            
        for (int k = 0; k < i + 1; k++)
            printf("#");
        printf("\n");
    }
}
