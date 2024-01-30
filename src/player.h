#ifndef PLAYER_H
#define PLAYER_H

#include <inttypes.h>
#include <stdbool.h>
#include "tile.h"

struct Player {
    money cash;
    uint8_t boardIndex;
    uint8_t playerIndex;
    bool inJail;
    uint8_t turnsInJail;
    bool stillPlaying;
};

bool player_buyProperty( struct Player *player, struct Tile *property ); 
bool player_mortgageProperty( struct Player *player, struct Tile *property );

#endif
