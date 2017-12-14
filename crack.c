/*
    Bill Combs - Updated to remove string type and use pointers
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* crack(char* userHash, char* salt);

int main(int argc, char* argv[])

{
    if(argc != 2 || strlen(argv[1]) != 13)
    {
        printf("Usage: ./crack hashkey(13 characters)\n");
        return 1;
    }

    // Get the hash entered
    char* userHash = argv[1];

    // Get the salt
    char* salt =  malloc(3 * sizeof(char));
    strncpy(salt, argv[1], 2);
   
    // Allocate memory for the password and copy what crack() returns into it
    char* password = malloc(5 * sizeof(char));
    strncpy(password, crack(userHash, salt), 4);


    // Print the password to the user
    printf("%s\n", password);
    
    // Free all of the memory we have malloc'd
    free(salt);
    free(password);

    return 0;
}

// This function cracks the hash the user entered at command line
char* crack(char* userHash, char* salt)
{
    // Stores the hash we generate from the crypt() function
    char* hash = NULL;

    // If the hashes match, this string will be set to the attempt and returned
    char* password = NULL;

    // Returned if the password isn't found
    char* notFound = "Password not cracked";

    // Stores alphabet upper and lowercase so there is no toupper() and tolower() conversions
    char alphabet[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    //Stores the length of alphabet
    int length = strlen(alphabet);

    // Stores the attempt we are hashing and trying                     
    char attempt[5];

    // Check for a one char password
    for(int i = 0; i < length; i++)
    {
        // Set the first char
          attempt[0] = alphabet[i];

        // Hash attempt and see if it matches userHash
        hash = crypt(attempt, salt);
        if(strcmp(hash, userHash) == 0)
        {
            password = attempt;
            return password;
        }
    }
        
    // Check for two chars
    for(int i = 0; i < length; i++)
    {
        // Set the first char
        attempt[0] = alphabet[i];

        for(int j = 0; j < length; j++)
        {
            // Set the second char
            attempt[1] = alphabet[j];

            // Hash attempt with two chars and see if it matches userHash
            hash = crypt(attempt, salt);
            if(strcmp(hash, userHash) == 0)
            {
                password = attempt;
                return password;
            }
        }
    }

    // Check for three chars
    for(int i = 0; i < length; i++)
    {
        // Set the first char
        attempt[0] = alphabet[i];

        for(int j = 0; j < length; j++)
        {
            // Set the second char
            attempt[1] = alphabet[j];

            for(int k = 0; k < length; k++)
            {
                // Set the third char
                attempt[2] = alphabet[k];

                // Hash attempt with three chars and see if it matches userHash
                hash = crypt(attempt, salt);
                if(strcmp(hash, userHash) == 0)
                {
                    password = attempt;
                    return password;
                }
            }
        }
    }

    // Check for four chars
    for(int i = 0; i < length; i++)
    {
        // Set the first char
        attempt[0] = alphabet[i];
        
        for(int j = 0; j < length; j++)
        {
            // Set the second char
            attempt[1] = alphabet[j];

            for(int k = 0; k < length; k++)
            {
                // Set the third char
                attempt[2] = alphabet[k];

                for(int l = 0; l < length; l++)
                {
                    // Set the fourth char
                    attempt[3] = alphabet[l];
                    
                    // Hash attempt with four chars and see if it matches userHash
                    hash = crypt(attempt, salt);
                    if(strcmp(hash, userHash) == 0)
                    {
                        password = attempt;
                        return password;
                    }
                }
            }
        }
    }

    // Returns if the password isn't found
    return notFound;
}