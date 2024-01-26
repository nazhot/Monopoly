#ifndef TILE_H
#define TILE_H

#include <inttypes.h>
#include <stdbool.h>

typedef unsigned int money;

enum PropType {
    PROPERTY,
    UTILITY,
    RAILROAD,
    FREE_PARKING,
    JAIL,
    GO_TO_JAIL,
    COMMUNITY_CHEST,
    CHANCE,
    GO,
    TAX
};

struct Tile {
    char *name;
    money cost;
    money rent;
    money mortgageValue;
    enum PropType type;
    uint8_t group;
    bool isMortgaged;
    uint8_t ownerIndex;
    bool isOwned;
    uint8_t numHouses;
    uint8_t numHotels;
};

#endif
