#ifndef RENDERER_H
#define RENDERER_H

#include "raylib.h"
#include "../engine/battlefield.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 850

#define TILE_SIZE 80
#define BOARD_SIZE 8

#define BOARD_X 180
#define BOARD_Y 120

void drawHeader(char currentTurn);

void drawBattlefield(
    Battlefield *arena,
    int selectedRow,
    int selectedCol
);

void drawVictoryScreen(int winner);

#endif