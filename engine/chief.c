#include <stdio.h>

#include "../engine/battlefield.h"
#include "clanwar.h"
#include "warrior.h"

int main()
{

    Battlefield arena;
    Warrior redChief, blackChief;

    prepareWar(&arena);
    showWar(&arena);
    showStats(&arena);

    printf("====================================\n");
    printf("         CHECKERS GAME\n");
    printf("====================================\n\n");

    printf("Enter Red Player Name: ");
    scanf("%49s", redChief.playerName);

    printf("Enter Black Player Name: ");
    scanf("%49s", blackChief.playerName);

    redChief.troopType = 'r';
    blackChief.troopType = 'b';

    int turn = 1;

    while (1)
    {
        showWar(&arena);

        Warrior currentPlayer;

        if (turn % 2 != 0)
        {
            currentPlayer = redChief;
        }
        else
        {
            currentPlayer = blackChief;
        }

        printf("\n------------------------------------\n");
        printf("Turn %d\n", turn);
        printf("%s's Turn (%c)\n",
               currentPlayer.playerName,
               currentPlayer.troopType);
        printf("------------------------------------\n");

        int fromRow, fromCol;
        int toRow, toCol;

        printf("Move From (row col): ");
        scanf("%d %d", &fromRow, &fromCol);

        printf("Move To (row col): ");
        scanf("%d %d", &toRow, &toCol);

        int result = makeMove(
            &arena,
            fromRow,
            fromCol,
            toRow,
            toCol
        );

        if (result == 0)
        {
            printf("\nInvalid Move! Try Again.\n");
            continue;
        }

        if (result == 2)
        {
            printf("\nPiece Captured!\n");
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

                printf("\nAnother Capture Available!\n");
                printf("Current Position: %d %d\n",
                       currentRow,
                       currentCol);

                int nextRow, nextCol;

                printf("Next Capture (row col): ");
                scanf("%d %d",
                      &nextRow,
                      &nextCol);

                int chainMove = makeMove(
                    &arena,
                    currentRow,
                    currentCol,
                    nextRow,
                    nextCol
                );

                if (chainMove != 2)
                {
                    printf("You must perform a capture!\n");
                    continue;
                }

                currentRow = nextRow;
                currentCol = nextCol;

                promoteHeroes(&arena);
            }
        }
        int winner = checkWinner(&arena);

        if (winner == 1)
        {
            showWar(&arena);
            showStats(&arena);

            printf("\n====================================\n");
            printf("Winner: %s\n",
                   redChief.playerName);
            printf("====================================\n");

            break;
        }

        if (winner == 2)
        {
            showWar(&arena);

            printf("\n====================================\n");
            printf("Winner: %s\n",
                   blackChief.playerName);
            printf("====================================\n");

            break;
        }

        turn++;
    }

    printf("\nThanks for playing!\n");

    return 0;
}