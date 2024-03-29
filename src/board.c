#include "board.h"
#include "card.h"
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
    struct Card cards[NUM_TYPES_OF_CARD][256];
    uint8_t numCards[NUM_TYPES_OF_CARD];
    uint8_t currentCardIndex[NUM_TYPES_OF_CARD];
    uint8_t goIndex;
    bool goAdded;
    uint8_t jailIndex;
    bool jailAdded;
    money passGoAmount;
};

static struct Board board;
bool initialized = false;

static void board_sendCurrentPlayerToJail() {
    struct Player *currentPlayer = &board.players[board.currentPlayerIndex];
    currentPlayer->inJail = true;
    currentPlayer->boardIndex = board.jailIndex;
    currentPlayer->turnsInJail = 0;
}

static void board_activateCard( enum CardAction action, union CardParameter param ) {
    switch ( action ) {
        case NO_ACTION:
            break;
        case ADVANCE_TO_NAME:
            break;
        case ADVANCE_TO_TYPE:
            break;
        case ADVANCE_TO_NAME_PAY_DOUBLE:
            break;
        case ADVANCE_TO_TYPE_PAY_DOUBLE:
            break;
        case EARN:
            break;
        case EARN_FROM_PLAYERS:
            break;
        case GET_OUT_OF_JAIL:
            break;
        case GO_BACK:
            break;
        case GO_TO_JAIL:
            break;
        case REPAIRS:
            break;
        case PAY:
            break;
        case PAY_EACH_PLAYER:
            break;
    }
}

static void board_drawCard( enum CardType type ) {
    struct Card card = board.cards[type][board.currentCardIndex[type]];


    board.currentCardIndex[type]++;
    board.currentCardIndex[type] %= board.numCards[type];
}


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
                                                .playerIndex = i,
                                                .stillPlaying = true,
                                              };
    }
    board.numPlayers = numPlayers;
    board.passGoAmount = 200;
}

void board_addTile( char *tileName, const money cost,
                    const money startingRent, const enum PropType type,
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
                                                        .mortgageValue = cost / 2,
                                                        .type = type,
                                                        .group = group,
                                                        .isMortgaged = false,
                                                        .isOwned = false,
                                                        .ownerIndex = 0,
                                                        .buildingCost = 0,
                                                        .startingRent = startingRent,
                                                        .currentRent = startingRent,
                                                      };
}

void board_addCard( char *title, enum CardType type, enum CardAction action1, 
                    union CardParameter parameter1,
                    enum CardAction action2,
                    union CardParameter parameter2 ) {
    assert( initialized && board.numCards[type] < 255 );
    board.cards[type][board.numCards[type]++] = ( struct Card ) 
                                                { .title = title, 
                                                  .action1 = action1, 
                                                  .parameter1 = parameter1,
                                                  .action2 = action2,
                                                  .parameter2 = parameter2
                                                };
}

void board_playTurn() {
    struct Player *currentPlayer = &board.players[board.currentPlayerIndex];
    if ( !currentPlayer->stillPlaying ) {
        board.currentPlayerIndex++;
        board.currentPlayerIndex %= board.numPlayers;
        return;
    }
    printf( "Current Player: %i\n", board.currentPlayerIndex );
    printf( "Current Tile: %s (%i)\n", board.tiles[currentPlayer->boardIndex].name, currentPlayer->boardIndex );
    for ( int i = 0; i < 3; ++i ) {
        uint8_t spacesToGo = board.goIndex > currentPlayer->boardIndex ?
                             board.goIndex - currentPlayer->boardIndex :
                             board.numTiles - currentPlayer->boardIndex + board.goIndex;
        printf( "Spaces to GO: %u\n", spacesToGo );
        uint8_t roll1 = rollDie( 6 ); 
        uint8_t roll2 = rollDie( 6 );
        printf( "Rolls: %u & %u\n", roll1, roll2 );
        if ( i == 2 && roll1 == roll2 ) {
            printf( "Too many doubles, to jail!\n" );
            currentPlayer->boardIndex = board.jailIndex;
            currentPlayer->inJail = true;
            break;
        }
        //move player
        currentPlayer->boardIndex += roll1 + roll2;
        currentPlayer->boardIndex %= board.numTiles;
        printf( "New Tile: %s (%i)\n", board.tiles[currentPlayer->boardIndex].name, currentPlayer->boardIndex );
        if ( roll1 + roll2 >= spacesToGo ) {
            printf( "Passed GO!\n" );
            currentPlayer->cash += board.passGoAmount;
        }

        //check Tile landed on
        struct Tile *currentTile = &board.tiles[currentPlayer->boardIndex];
        switch( currentTile->type ) {
            case PROPERTY:
            case UTILITY:
                {
                    money rentDue = currentTile->type == PROPERTY ? currentTile->currentRent :
                                    ( roll1 + roll2 ) * 4;
                    if ( currentTile->isOwned && !currentTile->isMortgaged &&
                        currentTile->ownerIndex != board.currentPlayerIndex ) {
                        if( rentDue > currentPlayer->cash ) {
                            //try to mortgage
                            printf( "Not enough money for rent!\n" );
                            break;
                        }
                        printf( "Paying $%u in rent to %u\n", rentDue, currentTile->ownerIndex );
                        currentPlayer->cash -= rentDue;
                        board.players[currentTile->ownerIndex].cash += rentDue;
                    } else if ( !currentTile->isOwned ) {
                        //check if player wants to buy, attempt to buy
                        printf( "Buy property\n" );
                        player_buyProperty( currentPlayer, currentTile );
                    }
                    break;
                }
            case TAX:
                if ( currentTile->currentRent > currentPlayer->cash ) {
                    //check for mortgages
                }
                currentPlayer->cash -= currentTile->currentRent;
                break;
            case CHANCE:
                break;
            case COMMUNITY_CHEST:
                break;
            case SEND_TO_JAIL:
                board_sendCurrentPlayerToJail();
                break;
            default:
                break;
        }

        if ( roll1 != roll2 ) {
            break;
        }
    }
    board.currentPlayerIndex++;
    board.currentPlayerIndex %= board.numPlayers;
}
