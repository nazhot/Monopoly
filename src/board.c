#include "board.h"
#include "player.h"
#include "tile.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


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
    uint8_t goIndex;
    bool goAdded;
    uint8_t jailIndex;
    bool jailAdded;
    money passGoAmount;
};

static struct Board board;
bool initialized = false;

//Code from https://stackoverflow.com/questions/822323/how-to-generate-a-random-int-in-c
static uint8_t rollDie( const uint8_t die ) {
    if ((die - 1) == RAND_MAX) {
        return rand();
    } else {
        // Supporting larger values for n would requires an even more
        // elaborate implementation that combines multiple calls to rand()
        // Chop off all of the values that would cause skew...
        int end = RAND_MAX / die; // truncate skew
        assert (end > 0);
        end *= die;

        // ... and ignore results from rand() that fall above that limit.
        // (Worst case the loop condition should succeed 50% of the time,
        // so we can expect to bail out of this loop pretty quickly.)
        int r;
        while ((r = rand()) >= end);

        return 1 + r % die;
      }
}

void board_initialize( const uint8_t numPlayers ) {
    initialized = true;
    board = ( struct Board ){0};
    for ( int i = 0; i < numPlayers; ++i ) {
        board.players[i] = ( struct Player ) {
                                                .cash = 1500,
                                                .boardIndex = 0,
                                                .inJail = false,
                                              };
    }
    board.numPlayers = numPlayers;
    board.passGoAmount = 200;
}
void board_addTile( char *tileName, const money cost,
                    const money mortgage, const enum PropType type,
                    const uint8_t group ) {
    assert( initialized && board.numTiles < 255 );
    assert( !( board.goAdded && type == GO ) );
    assert( !( board.jailAdded && type == JAIL ) );

    if ( type == JAIL ) {
        board.jailAdded = true;
        board.jailIndex = board.numTiles;
    }
    if ( type == GO ) {
        board.goAdded = true;
        board.goIndex = board.numTiles;
    }
    board.tiles[board.numTiles++] = ( struct Tile ) {
                                                        .name = tileName,
                                                        .cost = cost,
                                                        .mortgageValue = mortgage,
                                                        .type = type,
                                                        .group = group,
                                                        .isMortgaged = false,
                                                        .isOwned = false,
                                                        .ownerIndex = 0,
                                                        .buildingCost = 0
                                                      };
}

void board_playTurn() {
    struct Player currentPlayer = board.players[board.currentPlayerIndex];
    printf( "Current Player: %i\n", board.currentPlayerIndex );
    printf( "Current Tile: %s (%i)\n", board.tiles[currentPlayer.boardIndex].name, currentPlayer.boardIndex );
    for ( int i = 0; i < 3; ++i ) {
        uint8_t spacesToGo = board.goIndex > currentPlayer.boardIndex ?
                             board.goIndex - currentPlayer.boardIndex :
                             board.numTiles - currentPlayer.boardIndex + board.goIndex;
        printf( "Spaces to GO: %u\n", spacesToGo );
        uint8_t roll1 = rollDie( 6 ); 
        uint8_t roll2 = rollDie( 6 );
        printf( "Rolls: %u & %u\n", roll1, roll2 );
        if ( i == 2 && roll1 == roll2 ) {
            printf( "Too many doubles, to jail!\n" );
            currentPlayer.boardIndex = board.jailIndex;
            currentPlayer.inJail = true;
            break;
        }
        //move player
        currentPlayer.boardIndex += roll1 + roll2;
        currentPlayer.boardIndex %= board.numTiles;
        printf( "New Tile: %s (%i)\n", board.tiles[currentPlayer.boardIndex].name, currentPlayer.boardIndex );
        if ( roll1 + roll2 >= spacesToGo ) {
            printf( "Passed GO!\n" );
            currentPlayer.cash += board.passGoAmount;
        }

        //check Tile landed on
        struct Tile currentTile = board.tiles[currentPlayer.boardIndex];
        switch( currentTile.type ) {
            case PROPERTY:
            case UTILITY:
                {
                    money rentDue = currentTile.type == PROPERTY ? currentTile.currentRent :
                                    ( roll1 + roll2 ) * 4;
                    if ( currentTile.isOwned && !currentTile.isMortgaged &&
                         currentTile.ownerIndex != board.currentPlayerIndex ) {
                        if( rentDue > currentPlayer.cash ) {
                            //try to mortgage
                        }
                        currentPlayer.cash -= rentDue;
                        board.players[currentTile.ownerIndex].cash += rentDue;
                    } else if ( !currentTile.isOwned ) {
                        //check if player wants to buy, attempt to buy
                    }
                    break;
                }
            case TAX:
                if ( currentTile.currentRent > currentPlayer.cash ) {
                    //check for mortgages
                }
                currentPlayer.cash -= currentTile.currentRent;
                break;
            case CHANCE:
                break;
            case COMMUNITY_CHEST:
                break;
            default:
                break;
        }

        if ( roll1 != roll2 ) {
            break;
        }
    }
    board.players[board.currentPlayerIndex] = currentPlayer;
    board.currentPlayerIndex++;
    board.currentPlayerIndex %= board.numPlayers;
}
