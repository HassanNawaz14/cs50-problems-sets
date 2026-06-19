#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Enetr n: ");
    }
    while (n <= 0 || n > 8);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - (i + 1); j++)
        {
            printf(" ");
        }
        for (int j = 2 * (i) + 3; j > 0; j--)
        {
            if (j == i + 2)
            {
                printf("  ");
                continue;
            }
            printf("#");
        }
        printf("\n");
    }
}
