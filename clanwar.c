#include "clanwar.h"

int isLegalRaid(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol,
                char troop)
{
    if(toRow < 0 || toRow >= WAR_MAP)
        return 0;

    if(toCol < 0 || toCol >= WAR_MAP)
        return 0;

    if(arena->troops[toRow][toCol] != '.')
        return 0;

    if(troop == 'r')
    {
        if(toRow == fromRow - 1 &&
           (toCol == fromCol - 1 ||
            toCol == fromCol + 1))
            return 1;
    }

    if(troop == 'b')
    {
        if(toRow == fromRow + 1 &&
           (toCol == fromCol - 1 ||
            toCol == fromCol + 1))
            return 1;
    }

    return 0;
}

void launchRaid(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol)
{
    arena->troops[toRow][toCol]
        = arena->troops[fromRow][fromCol];

    arena->troops[fromRow][fromCol]
        = '.';
}

void promoteHeroes(Battlefield *arena)
{
    for(int tower=0; tower<WAR_MAP; tower++)
    {
        if(arena->troops[0][tower] == 'r')
            arena->troops[0][tower] = 'R';

        if(arena->troops[WAR_MAP-1][tower] == 'b')
            arena->troops[WAR_MAP-1][tower] = 'B';
    }
}

int checkClanDestroyed(Battlefield *arena)
{
    int redClan = 0;
    int blackClan = 0;

    for(int row=0; row<WAR_MAP; row++)
    {
        for(int col=0; col<WAR_MAP; col++)
        {
            if(arena->troops[row][col] == 'r' ||
               arena->troops[row][col] == 'R')
                redClan++;

            if(arena->troops[row][col] == 'b' ||
               arena->troops[row][col] == 'B')
                blackClan++;
        }
    }

    if(redClan == 0)
        return 2;

    if(blackClan == 0)
        return 1;

    return 0;
}