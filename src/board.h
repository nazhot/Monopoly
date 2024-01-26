#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <inttypes.h>
#include "card.h"
#include "player.h"
#include "tile.h"

struct Board {
    struct Player players[256];
    uint8_t numPlayers;
    struct Tile tiles[256];
    uint8_t numTiles;
    uint8_t currentPlayerIndex;
    struct Card chanceCards[256];
    uint8_t numChanceCards;
    uint8_t currentChanceCardIndex;
    struct Card communityChestCards[256];
    uint8_t numCommunityChestCards;
    uint8_t currentCommunityChestCardIndex;
};

struct Board* board_initialize( const uint8_t numPlayers );
void board_addTile( const char *tileName, const money cost, const money mortgage,
                    const enum PropType type, const uint8_t group );

#endif
