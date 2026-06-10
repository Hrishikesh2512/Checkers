#include "raylib.h"

#include "../engine/battlefield.h"
#include "../engine/clanwar.h"

#include "renderer.h"
#include "input.h"

int main(void)
{
    InitWindow(
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        "Clan Dominion"
    );

    SetTargetFPS(60);

    Battlefield arena;
    prepareWar(&arena);

    InputState inputState;
    initializeInput(&inputState);

    char currentTurn = 'r';

    while (!WindowShouldClose())
    {
        int winner =
            checkWinner(&arena);

        if (winner == 0)
        {
            handleMouseInput(
                &arena,
                &inputState,
                &currentTurn
            );
        }

        BeginDrawing();

        ClearBackground(
            (Color){30,45,30,255}
        );

        drawHeader(
            currentTurn
        );

        drawBattlefield(
            &arena,
            inputState.selectedRow,
            inputState.selectedCol
        );

        drawVictoryScreen(
            winner
        );

        EndDrawing();
    }

    CloseWindow();

    return 0;
}