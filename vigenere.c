#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

string encipher(string p, string k);

int main(int argc, string argv[])
{
    // Will hold the key user enters at command line
    string k;
    
    // Make sure the correct command-line arguments were entered
    if(argc != 2)
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
    else
    {
        k = argv[1];
        
        //Check to see if key contains only alphabetic characters
        for(int i = 0, n = strlen(k); i < n; i++)
        {
            if(!isalpha(k[i]))
            {
                printf("Please enter only alphabetic letters.\n");
                return 1;
            }
        }
    }
    
    // Prompt user for plaintext
    printf("plaintext: ");
    string p = get_string();
    
    // If get_string() returned a strings
    if(p != NULL)
    {
        // Encrypt the plaintext
        string ciphertext = encipher(p, k);
        
        // Print the ciphertext
        printf("ciphertext: %s\n", ciphertext);
    }
    
    return 0;
}

// Enciphers the plaintext and returns ciphertext
string encipher(string p, string k)
{
    // Convert k to lower case since 'A' and 'a' will have the same value
    for(int i = 0; i < strlen(k); i++)
    {
        k[i] = tolower(k[i]);
    }
    
    // Counter for k
    int j = 0;
    
    // Alphabetical indices for p and k, and the integer of the enciphered char
    int pAIndex, kAIndex, cipher;
    
    // Iterate through the string and encipher each char, skipping any non-letters
    for(int i = 0, pLength = strlen(p), kLength = strlen(k); i < pLength; i++)
    {
        if(isalpha(p[i]))
        {
            // If counter j is equal to or greater than kLength, wrap it around
            if(j == kLength)
            {
                j = j % kLength;
            }
            
            // Set alphabetical index of the key
            kAIndex = k[j] - 97;
            
            if(isupper(p[i]))
            {
                p[i] = tolower(p[i]);
                pAIndex = p[i] - 97;
                cipher = ((pAIndex + kAIndex) % 26) + 97;
                
                // Enciper preserving case
                p[i] = toupper(cipher);
            }
            else
            {
                pAIndex = p[i] - 97;
                cipher = ((pAIndex + kAIndex) % 26) + 97;
                
                // Encipher preserving case
                p[i] = tolower(cipher);
            }
            
            // Move to the next position in k
            j++;
        }
    }
    
    // Return the ciphertext
    return p;
}