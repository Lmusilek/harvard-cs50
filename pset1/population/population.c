#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("Starting populaion size: ");
    }
    while (s < 9);
    // TODO: Prompt for end size
    int e;
    do
    {
        e = get_int("Ending population size: ");
    }
    while (e < s);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int population = s;
    while (population < e)
    {
        population = population + (population / 3) - (population / 4);
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}