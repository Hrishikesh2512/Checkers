#include <stdio.h>
#include "battlefield.h"

void prepareWar(Battlefield *arena)
{
    for (int row = 0; row < WAR_MAP; row++)
    {
        for (int col = 0; col < WAR_MAP; col++)
        {
            arena->troops[row][col] = '.';
        }
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < WAR_MAP; col++)
        {
            if ((row + col) % 2 == 1)
            {
                arena->troops[row][col] = 'b';
            }
        }
    }

    for (int row = 5; row < WAR_MAP; row++)
    {
        for (int col = 0; col < WAR_MAP; col++)
        {
            if ((row + col) % 2 == 1)
            {
                arena->troops[row][col] = 'r';
            }
        }
    }
}

void showWar(Battlefield *arena)
{
    printf("\n");

    printf("   ");
    for (int col = 0; col < WAR_MAP; col++)
    {
        printf("%d ", col);
    }

    printf("\n");

    for (int row = 0; row < WAR_MAP; row++)
    {
        printf("%d  ", row);

        for (int col = 0; col < WAR_MAP; col++)
        {
            printf("%c ", arena->troops[row][col]);
        }

        printf("\n");
    }

    printf("\n");
}