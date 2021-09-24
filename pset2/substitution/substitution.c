#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])

// VALIDATIONS START..........................
{
    //Checks correct number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
    //Check the key is 26 letters long
    if (strlen(argv[1]) != 26)
    {
        printf("Key must be 26 characters long\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // Checks that only letters are used
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Must contain only letters.\n");
            return 1;
        }
        else if (islower(argv[1][i]) != 0)
        {
            argv[1][i] = toupper(argv[1][i]);
        }
    }
    //Checks for repeated letters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        for (int k = i + 1; k <= 26; k++)
        {
            if (argv[1][i] == argv[1][k])
            {
                printf("Must not contain duplicate letters\n");
                return 1;
            }

        }
    }
// VALIDATIONS END..........................

    // Ask for text
    string plaintext = get_string("plaintext: ");
    char ciphertext[strlen(plaintext) + 1];

    // Convert to ciphertext
    const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(plaintext); i++)
    {
        //Upper case letters cypher
        if (isupper(plaintext[i]) != 0)
        {
            for (int j = 0; j < 26; j++)
            {
                if (plaintext[i] == alphabet[j])
                {
                    ciphertext[i] = argv[1][j];
                }
            }
        }
        //Lower case letters cypher
        else if (islower(plaintext[i]) != 0)
        {
            for (int j = 0; j < strlen(alphabet); j++)
            {
                if (plaintext[i] == tolower(alphabet[j]))
                {
                    ciphertext[i] = tolower(argv[1][j]);
                }
            }
        }
        //Keep other characters
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}