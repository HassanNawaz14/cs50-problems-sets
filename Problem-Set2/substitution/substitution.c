#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

string encrypt(string key, string plaint)
{
    string ciphert = plaint;

    int i;
    for (i = 0; plaint[i] != '\0'; i++)
    {
        if (!isalpha(plaint[i]))
        {
            continue;
        }
        int index;
        if (islower(plaint[i]))
        {
            index = plaint[i] - 'a';
            if (isupper(key[index]))
            {
                ciphert[i] = (key[index] + 32);
            }
            else
            {
                ciphert[i] = (key[index]);
            }
        }
        else
        {
            index = plaint[i] - 'A';
            if (islower(key[index]))
            {
                ciphert[i] = (key[index] - 32);
            }
            else
            {
                ciphert[i] = (key[index]);
            }
        }
        // printf("index = %i\n", index);
        // printf("key[index] = %c\n", key[index]);
    }
    ciphert[i] = '\0';
    return ciphert;
}

int main(int argc, string argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; argv[1][i]; i++)
    {
        if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        for (int j = 0; argv[1][j] != '\0'; j++)
        {
            if (j != i && (argv[1][j] == argv[1][i] || argv[1][j] == argv[1][i] + 32 ||
                           argv[1][j] == argv[1][i] - 32))
            {
                printf("Key must contain 26 UNIQUE characters.\n");
                return 1;
            }
        }
    }

    string plaint = get_string("plaintext:  ");

    printf("ciphertext: %s\n", encrypt(argv[1], plaint));
    return 0;
}
