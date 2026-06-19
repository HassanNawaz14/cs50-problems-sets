#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // getting name
    string name = get_string("What's your name? ");
    // printing hello, name
    printf("hello, %s\n", name);
}
