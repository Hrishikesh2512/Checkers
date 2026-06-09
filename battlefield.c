#include <stdio.h>
#include "battlefield.h"

void prepareWar(Battlefield *arena)
{
    for(int lane=0; lane<WAR_MAP; lane++)
    {
        for(int tile=0; tile<WAR_MAP; tile++)
        {
            arena->troops[lane][tile] = '.';
        }
    }

    for(int lane=0; lane<3; lane++)
    {
        for(int tile=0; tile<WAR_MAP; tile++)
        {
            if((lane + tile) % 2)
            {
                arena->troops[lane][tile] = 'b';
            }
        }
    }

    for(int lane=5; lane<WAR_MAP; lane++)
    {
        for(int tile=0; tile<WAR_MAP; tile++)
        {
            if((lane + tile) % 2)
            {
                arena->troops[lane][tile] = 'r';
            }
        }
    }
}

void showWar(Battlefield *arena)
{
    printf("\n   ");

    for(int tile=0; tile<WAR_MAP; tile++)
    {
        printf("%d ", tile);
    }

    printf("\n");

    for(int lane=0; lane<WAR_MAP; lane++)
    {
        printf("%d  ", lane);

        for(int tile=0; tile<WAR_MAP; tile++)
        {
            printf("%c ", arena->troops[lane][tile]);
        }

        printf("\n");
    }
}