#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float rest;
    int counter = 0;
    
    //user enters greedy until it is more than zero
    do
    {
        printf("Enter the rest, please: ");
        rest = GetFloat();
    }
    while (rest <= 0);
    
    //work with dollars   
    int dollars = round(rest);
    if (dollars > rest)
        dollars--;
    int dollars_rest = dollars * 4;
    counter += dollars_rest;   
    printf("%d", counter);
    
    //work with cents
    int cents = (rest - dollars) * 100;
    cents = round(cents);
    do
    {
        if (cents >= 25)
        {
            cents -= 25;
            counter++;
        }
        else if (cents >= 10 && cents < 25)
        {
            cents -= 10;
            counter++;
        }
        else if (cents >= 5 && cents < 10)
        {
            cents -= 5;
            counter++;
        }
        else if (cents >= 1 && cents < 5)
        {
            cents -= 1;
            counter++;
        }
        printf("cents: %d\n", cents);
    }
    while (cents >= 1);
    
    printf("%d\n", counter);
}
