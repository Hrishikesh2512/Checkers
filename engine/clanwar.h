#ifndef CLANWAR_H
#define CLANWAR_H

#include "../engine/battlefield.h"
void showStats(Battlefield *arena);

void showStats(Battlefield *arena);

void showStats(Battlefield *arena);

int insideMap(int row, int col);

int isRedPiece(char piece);
int isBlackPiece(char piece);
int isKing(char piece);

int canCapture(Battlefield *arena,
               int row,
               int col);

int playerHasCapture(Battlefield *arena,
                     char troop);

int isLegalMove(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol,
                char troop);

int makeMove(Battlefield *arena,
             int fromRow,
             int fromCol,
             int toRow,
             int toCol);

void promoteHeroes(Battlefield *arena);

int playerHasMoves(Battlefield *arena,
                   char troop);

int checkWinner(Battlefield *arena);

#endif