/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 512




int main(int argc, char* argv[])
{


    //open the card file
    FILE* card = fopen("card.raw", "r");
      
      
    if (card == NULL)
    {
        fclose(card);
        printf("Could not open file.\n");
        return 1;
    }
    
    int open = 0;
    uint8_t block[BUFFER_SIZE];
    
    //cheks for first four bytes
    uint8_t checkjpg1[4] = {0xff, 0xd8, 0xff, 0xe0};
    uint8_t checkjpg2[4] = {0xff, 0xd8, 0xff, 0xe1};
    
    
    uint8_t check[4];
    int counter = 0;
    FILE *img;
    
    //read 512 bytes to block from card
    fread(block, 512, 1, card); 
    while (fread(block, 512, 1, card) > 0)
    {
        for(int i = 0; i < 4; i++)
		{
				check[i] = block[i];
		}
    
        //if we found new jpg
        if((memcmp(checkjpg1, check, 4) == 0 ) || (memcmp(checkjpg2, check, sizeof(check)) == 0))
        {
            char title[8];
            sprintf(title, "%03d.jpg", counter);
            
            //create first jpg file
            if (open == 0)
            {
                img =  fopen(title, "w");
                fwrite(block, sizeof(block), 1, img);
				open = 1;
			}
			
			//create new jpg file
			if(open == 1)
			{
					fclose(img);
					img = fopen(title, "w");
					fwrite(block, sizeof(block), 1, img);
					counter++;
            }
        }
        
        //if new jpg file is not found
        else if (open)
        {
            fwrite(block, sizeof(block), 1, img);
        }
        
    }
    
    
    if(img)
    {
        fclose(img);
    }
 
 
    fclose(card);   
    return 0;
}
