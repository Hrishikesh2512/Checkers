#include "input.h"
#include "renderer.h"

void initializeInput(InputState *state)
{
    state->selectedRow = -1;
    state->selectedCol = -1;
}

void handleMouseInput(
    Battlefield *arena,
    InputState *state,
    char *currentTurn
)
{
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        return;
    }

    Vector2 mouse =
        GetMousePosition();

    int col =
        (mouse.x - BOARD_X) /
        TILE_SIZE;

    int row =
        (mouse.y - BOARD_Y) /
        TILE_SIZE;

    if (row < 0 ||
        row >= BOARD_SIZE ||
        col < 0 ||
        col >= BOARD_SIZE)
    {
        return;
    }

    if (state->selectedRow == -1)
    {
        char troop =
            arena->troops[row][col];

        if (*currentTurn == 'r')
        {
            if (troop == 'r' ||
                troop == 'R')
            {
                state->selectedRow = row;
                state->selectedCol = col;
            }
        }

        if (*currentTurn == 'b')
        {
            if (troop == 'b' ||
                troop == 'B')
            {
                state->selectedRow = row;
                state->selectedCol = col;
            }
        }

        return;
    }

    int moveResult =
        makeMove(
            arena,
            state->selectedRow,
            state->selectedCol,
            row,
            col
        );

    if (moveResult)
    {
        promoteHeroes(arena);

        if (*currentTurn == 'r')
        {
            *currentTurn = 'b';
        }
        else
        {
            *currentTurn = 'r';
        }
    }

    state->selectedRow = -1;
    state->selectedCol = -1;
}