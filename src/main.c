#include "board.h"
#include "card.h"
#include "tile.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
    board_initialize( 4 );
    board_addTile( "GO", 0, 0, GO, 99 );
    board_addTile( "Mediterranean Avenue", 60, 2, PROPERTY, 0);
    board_addTile( "Community Chest", 0, 0, COMMUNITY_CHEST, 0);
    board_addTile( "Baltic Avenue", 60, 4, PROPERTY, 100);
    board_addTile( "Income Tax", 200, 0, TAX, 101);
    board_addTile( "Reading Railroad", 200, 25, RAILROAD, 1);
    board_addTile( "Oriental Avenue", 100, 6, PROPERTY, 2);
    board_addTile( "Vermont Avenue", 100, 6, PROPERTY, 2);
    board_addTile( "Conneticut Avenue", 120, 8, PROPERTY, 2);
    board_addTile( "Jail", 0, 0, JAIL, 102 );

    union CardParameter noParam = ( union CardParameter) ( money ) 0;

    board_addCard( "Advance to Boardwalk", CARD_CHANCE, ADVANCE_TO_NAME,
                   ( union CardParameter ) "Boardwalk", NO_ACTION, noParam );
    board_addCard( "Advance to Go (Collect $200)", CARD_CHANCE, ADVANCE_TO_TYPE,
                   ( union CardParameter ) ( enum PropType ) GO, NO_ACTION,
                   noParam );
    board_addCard( "Advance to Illinois Ave.",
                   CARD_CHANCE, ADVANCE_TO_NAME,
                   ( union CardParameter ) "Illinois Avenue", NO_ACTION, noParam );
    board_addCard( "Advance to St. Charles Place. If you pass Go, collect $200",
                   CARD_CHANCE, ADVANCE_TO_NAME,
                   ( union CardParameter ) "St. Charles Place", NO_ACTION,
                   noParam );
    board_addCard( "Advance token to the nearest Railroad and pay owner twice "
                   "the Rental to which he is otherwise entitled. If Railroad "
                   "is unowned, you may buy it from the Bank.", CARD_CHANCE,
                   ADVANCE_TO_TYPE_PAY_DOUBLE,
                   ( union CardParameter ) ( enum PropType ) RAILROAD, NO_ACTION,
                   noParam );
    board_addCard( "Advance token to the nearest Railroad and pay owner twice "
                   "the Rental to which he is otherwise entitled. If Railroad "
                   "is unowned, you may buy it from the Bank.", CARD_CHANCE,
                   ADVANCE_TO_TYPE_PAY_DOUBLE,
                   ( union CardParameter ) ( enum PropType ) UTILITY, NO_ACTION,
                   noParam );
    board_addCard( "Advance token to the nearest Utility and pay owner twice "
                   "the Rental to which he is otherwise entitled. If Railroad "
                   "is unowned, you may buy it from the Bank.", CARD_CHANCE,
                   ADVANCE_TO_TYPE_PAY_DOUBLE,
                   ( union CardParameter ) ( enum PropType ) RAILROAD, NO_ACTION,
                   noParam );
    board_addCard( "Bank pays you a dividend of $50", CARD_CHANCE, EARN,
                   ( union CardParameter ) ( money ) 50, NO_ACTION, noParam );
    board_addCard( "Get Out of Jail Free", CARD_CHANCE, GET_OUT_OF_JAIL,
                    noParam, NO_ACTION, noParam );



    for ( int i = 0; i < 10; ++i ) {
        board_playTurn();
    }

    return 0;
}
