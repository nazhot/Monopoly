#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <stdbool.h>
#include "tile.h"

struct Player {
    money cash;
    uint8_t boardIndex;
    bool inJail;
    uint8_t turnsInJail;
};

#endif
