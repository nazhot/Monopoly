#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include "tile.h"

struct Player {
    money cash;
    uint8_t boardIndex;
};

#endif
