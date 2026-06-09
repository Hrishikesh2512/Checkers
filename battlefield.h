#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#define WAR_MAP 8

typedef struct
{
    char troops[WAR_MAP][WAR_MAP];
} Battlefield;

void prepareWar(Battlefield *arena);
void showWar(Battlefield *arena);

#endif