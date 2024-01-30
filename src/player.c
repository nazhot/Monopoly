#include "player.h"
#include <stdio.h>
#include <stdlib.h>



bool player_buyProperty( struct Player *player, struct Tile *property ) {
    if ( player->cash < property->cost ) {
        //TODO: figure out mortgage attempt
        return false;
    }
    player->cash -= property->cost;
    property->ownerIndex = player->playerIndex;
    property->isOwned = true;
    return true;
}
bool player_mortgageProperty( struct Player *player, struct Tile *property ) {
    return false;
}
