#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int scr[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string p)
{
    int score = 0;

    for (int i = 0, len = strlen(p); i < len; i++)
    {
        if (isupper(p[i]))
        {
            score += scr[p[i] - 'A'];
        }
        else if (islower(p[i]))
        {
            score += scr[p[i] - 'a'];
        }
    }

    return score;
}

int main(void)
{
    // Prompt the user for two words
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    // Compute the score of each word
    int s1 = compute_score(p1);
    int s2 = compute_score(p2);

    if (s1 < s2)
    {
        printf("Player 2 wins!\n");
    }
    else if (s1 > s2)
    {
        printf("Player 1 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}
