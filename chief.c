#include <stdio.h>
#include "battlefield.h"
#include "clanwar.h"
#include "warrior.h"

int main()
{
    Battlefield arena;

    Warrior redChief;
    Warrior blackChief;

    prepareWar(&arena);

    printf("Red Clan Chief: ");
    scanf("%49s", redChief.playerName);

    printf("Black Clan Chief: ");
    scanf("%49s", blackChief.playerName);

    redChief.troopType = 'r';
    blackChief.troopType = 'b';

    int warRound = 0;

    while(1)
    {
        showWar(&arena);

        Warrior currentChief =
            (warRound % 2 == 0)
            ? redChief
            : blackChief;

        int fromRow, fromCol;
        int toRow, toCol;

        printf("%s's turn\n",
               currentChief.playerName);

        scanf("%d%d",
              &fromRow,
              &fromCol);

        scanf("%d%d",
              &toRow,
              &toCol);

        if(!isLegalRaid(&arena,
                        fromRow,
                        fromCol,
                        toRow,
                        toCol,
                        currentChief.troopType))
        {
            printf("Raid Failed!\n");
            continue;
        }

        launchRaid(&arena,
                   fromRow,
                   fromCol,
                   toRow,
                   toCol);

        promoteHeroes(&arena);

        int result =
            checkClanDestroyed(&arena);

        if(result)
        {
            printf("Clan War Finished!\n");
            break;
        }

        warRound++;
    }

    return 0;
}