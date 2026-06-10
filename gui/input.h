#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

#include "../engine/battlefield.h"
#include "../engine/clanwar.h"

typedef struct
{
    int selectedRow;
    int selectedCol;
} InputState;

void initializeInput(
    InputState *state
);

void handleMouseInput(
    Battlefield *arena,
    InputState *state,
    char *currentTurn
);

#endif