#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    printf("letters: %i\n", letters);
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    words++;
    printf("words: %i\n", words);
    return words;
}

int count_sentences(string text)
{
    int sen = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sen++;
        }
    }
    // words++;
    printf("sen: %i\n", sen);
    return sen;
}

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Compute the Coleman-Liau index
    float l = ((float) letters / words) * 100;
    float s = ((float) sentences / words) * 100;
    float index = 0.0588 * l - 0.296 * s - 15.8;

    int rounded = round(index);

    // Print the grade level
    if (rounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rounded >= 1 && rounded <= 16)
    {
        printf("Grade %i\n", rounded);
    }
    else
    {
        printf("Grade 16+\n");
    }
}
