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

    printf("Enter Red Player Name: ");
    scanf("%49s", redChief.playerName);

    printf("Enter Black Player Name: ");
    scanf("%49s", blackChief.playerName);

    redChief.troopType = 'r';
    blackChief.troopType = 'b';

    int turn = 0;

    while (1)
    {
        showWar(&arena);

        Warrior currentPlayer =
            (turn % 2 == 0)
            ? redChief
            : blackChief;

        int fromRow, fromCol;
        int toRow, toCol;

        printf("\n%s's Turn (%c)\n",
               currentPlayer.playerName,
               currentPlayer.troopType);

        printf("From Row Col: ");
        scanf("%d %d",
              &fromRow,
              &fromCol);

        printf("To Row Col: ");
        scanf("%d %d",
              &toRow,
              &toCol);

        int result =
            makeMove(&arena,
                     fromRow,
                     fromCol,
                     toRow,
                     toCol);

        if (result == 0)
        {
            printf("Invalid Move!\n");
            continue;
        }

        promoteHeroes(&arena);

        if (result == 2)
        {
            int currentRow = toRow;
            int currentCol = toCol;

            while (canCapture(&arena,
                              currentRow,
                              currentCol))
            {
                showWar(&arena);

                printf("\nAdditional Capture Available!\n");

                printf("Continue From %d %d\n",
                       currentRow,
                       currentCol);

                printf("Next Row Col: ");

                int nextRow;
                int nextCol;

                scanf("%d %d",
                      &nextRow,
                      &nextCol);

                int chainResult =
                    makeMove(&arena,
                             currentRow,
                             currentCol,
                             nextRow,
                             nextCol);

                if (chainResult != 2)
                {
                    printf("You must capture!\n");
                    continue;
                }

                currentRow = nextRow;
                currentCol = nextCol;

                promoteHeroes(&arena);
            }
        }

        int winner =
            checkWinner(&arena);

        if (winner == 1)
        {
            showWar(&arena);

            printf("\n");
            printf("%s Wins!\n",
                   redChief.playerName);

            break;
        }

        if (winner == 2)
        {
            showWar(&arena);

            printf("\n");
            printf("%s Wins!\n",
                   blackChief.playerName);

            break;
        }

        turn++;
    }

    return 0;
}