#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int textlength();
int calcwords();
int calcsentences();
int calcgrade();

int main(void)y

// Get a text from a user
{
    string s;
    {
        s = get_string("Text: ");
    }
    calcgrade(textlength(s), calcwords(s), calcsentences(s));
}

// Calculate number of letters
int textlength(string s)
{
    int length = 0;
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        isalpha(s[i]) ? length++ : false;
    }
    return length;
}

// Calculate number of words
int calcwords(string s)
{
    int words = 1;
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        isspace(s[i]) ? words++ : false;
    }
    return words;
}

// Calculate number of sentences
int calcsentences(string s)
{
    int sentences = 0;
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        s[i] == '.' || s[i] == '!' || s[i] == '?' ? sentences++ : false;
    }
    return sentences;
}
// Calculates grade number
int calcgrade(int letters, int words, int sentences)
{
    float L = (float) letters / words * 100.0;
    float S = (float) sentences / words * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index < 1)
    {
        return printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        return printf("Grade 16+\n");
    }
    else
    {
        return printf("Grade %d\n", (int) round(index));
    }
}
