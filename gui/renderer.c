#include "renderer.h"

void drawHeader(char currentTurn)
{
    DrawText(
        "CLAN DOMINION",
        300,
        20,
        40,
        GOLD
    );

    DrawText(
        currentTurn == 'r'
        ? "Red Clan Turn"
        : "Black Clan Turn",
        390,
        70,
        20,
        WHITE
    );
}

void drawBattlefield(
    Battlefield *arena,
    int selectedRow,
    int selectedCol
)
{
    Color grassLight =
        (Color){120,180,80,255};

    Color grassDark =
        (Color){80,140,60,255};

    for(int row = 0; row < BOARD_SIZE; row++)
    {
        for(int col = 0; col < BOARD_SIZE; col++)
        {
            Color tile;

            if((row + col) % 2 == 0)
            {
                tile = grassLight;
            }
            else
            {
                tile = grassDark;
            }

            DrawRectangle(
                BOARD_X + col * TILE_SIZE,
                BOARD_Y + row * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE,
                tile
            );

            if(row == selectedRow &&
               col == selectedCol)
            {
                DrawRectangleLinesEx(
                    (Rectangle)
                    {
                        BOARD_X + col * TILE_SIZE,
                        BOARD_Y + row * TILE_SIZE,
                        TILE_SIZE,
                        TILE_SIZE
                    },
                    4,
                    GOLD
                );
            }

            char troop =
                arena->troops[row][col];

            int centerX =
                BOARD_X +
                col * TILE_SIZE +
                TILE_SIZE / 2;

            int centerY =
                BOARD_Y +
                row * TILE_SIZE +
                TILE_SIZE / 2;

            if(troop == 'r')
            {
                DrawCircle(
                    centerX,
                    centerY,
                    28,
                    RED
                );
            }

            if(troop == 'b')
            {
                DrawCircle(
                    centerX,
                    centerY,
                    28,
                    BLACK
                );
            }

            if(troop == 'R')
            {
                DrawCircle(
                    centerX,
                    centerY,
                    30,
                    RED
                );

                DrawText(
                    "K",
                    centerX - 8,
                    centerY - 12,
                    24,
                    GOLD
                );
            }

            if(troop == 'B')
            {
                DrawCircle(
                    centerX,
                    centerY,
                    30,
                    BLACK
                );

                DrawText(
                    "K",
                    centerX - 8,
                    centerY - 12,
                    24,
                    GOLD
                );
            }
        }
    }

    DrawRectangleLines(
        BOARD_X - 3,
        BOARD_Y - 3,
        BOARD_SIZE * TILE_SIZE + 6,
        BOARD_SIZE * TILE_SIZE + 6,
        GOLD
    );
}

void drawVictoryScreen(int winner)
{
    if(winner == 0)
    {
        return;
    }

    DrawRectangle(
        250,
        350,
        500,
        120,
        Fade(BLACK, 0.8f)
    );

    if(winner == 1)
    {
        DrawText(
            "RED CLAN VICTORY",
            285,
            390,
            35,
            GOLD
        );
    }

    if(winner == 2)
    {
        DrawText(
            "BLACK CLAN VICTORY",
            255,
            390,
            35,
            GOLD
        );
    }
}