#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n = get_long("Enter card: ");

    int len = 0;
    long t = n;
    for (len = 0; t > 0; len++)
    {
        t /= 10;
    }

    printf("len: %i\n", len);

    t = n;
    int sum = 0;
    int sum_later = 0;
    for (int i = 0; i < len; i++)
    {
        int r = t % 10;
        t /= 10;
        if (i % 2 != 0)
        {
            int prod = (r * 2);
            while (prod > 0)
            {
                int p = prod % 10;
                sum += p;
                prod /= 10;
            }
        }
        else
        {
            sum_later += r;
        }
    }
    int final = sum + sum_later;
    // printf("sum: %d\n", sum);
    // printf("sum later: %d\n", sum_later);
    // printf("final: %d\n", final);

    t = n;

    if (final % 10 == 0)
    {
        while (t > 99)
        {
            t /= 10;
        }
        int first_two_digit = t;
        int first_digit = t / 10;
        if (len == 15 && first_two_digit == 37)
        {
            printf("AMEX\n");
        }
        else if (len == 16 && (first_two_digit == 51 || first_two_digit == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((len == 16 || len == 13) && first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
