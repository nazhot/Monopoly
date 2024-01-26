#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <inttypes.h>
#include "card.h"
#include "player.h"
#include "tile.h"


void board_initialize( const uint8_t numPlayers );
void board_addTile( char *tileName, const money cost, const money mortgage,
                    const enum PropType type, const uint8_t group );
void board_playTurn();

#endif
