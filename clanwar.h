#ifndef CLANWAR_H
#define CLANWAR_H

#include "battlefield.h"

int isLegalRaid(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol,
                char troop);

void launchRaid(Battlefield *arena,
                int fromRow,
                int fromCol,
                int toRow,
                int toCol);

void promoteHeroes(Battlefield *arena);

int checkClanDestroyed(Battlefield *arena);

#endif