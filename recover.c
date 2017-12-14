/*
 *  Recover JPEG images
 *  Bill Combs
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // The file to read
    char *infile = argv[1];
    
    FILE *inptr = fopen(infile, "r");
    if(inptr == NULL)
    {
        fprintf(stderr, "Could not open %s", infile);
        return 2;
    }
    
    // Create a buffer to hold data from the infile
    uint8_t buffer[512];
    
    // Counter for how many files we have found
    int fileNum = 0;
    
    // File name of the current JPEG
    char *filename = malloc(8 * sizeof(char));
    
    // Flag to see if we have already found an image
    _Bool found = 0;
    
    // Flag for end-of-file
    _Bool eof = 0;
    
    // Pointer for image file to write to
    FILE *img = NULL;
   
    while(!eof)
    {
        while(fread(buffer, 512, 1, inptr) == 1)
        {
            // Check the first four bytes and see if it is a JPEG
            if(buffer[0] == 0xff && 
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
                {
                    // If we have already found a JPEG, we need to close it and open a new one
                    if(found)
                    {
                        fclose(img);
                        found = 0;
                    }
                    // We found a JPEG. Create a file to write to
                     sprintf(filename, "%03i.jpg", fileNum);
                     
                     // Set found to true
                     found = 1;
                     
                     // Increment fileNum by one for next file, if there is one.
                     fileNum++;
                     
                     // Open the file to write
                     img = fopen(filename, "w");
                     if(img == NULL)
                     {
                         fprintf(stderr, "Could not open file %s\n", filename);
                         return 3;
                     }
                }
                
            // If it is not a new JPEG, but we have found one, write the data to the open JPEG
            if(found)
            {
                fwrite(buffer, 512, 1, img);
            }
        }
        
        // End of file has been reached
        eof = 1;
    }
   
   // Close the files
   free(filename);
   fclose(inptr);
   fclose(img);
}