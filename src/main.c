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
    board_addCard( "Go Back 3 Spaces", CARD_CHANCE, GO_BACK, 
                   ( union CardParameter ) ( uint8_t ) 3, NO_ACTION, noParam );
    board_addCard( "Go to Jail. Go directly to Jail, do not pass Go, do not "
                   "collect $200", CARD_CHANCE, GO_TO_JAIL, noParam, NO_ACTION,
                   noParam );
    board_addCard( "Make general repairs on all your property. For each house "
                   "pay $25. For each hotel pay $100", CARD_CHANCE, REPAIRS,
                   ( union CardParameter ) ( money ) 25, REPAIRS,
                   ( union CardParameter ) ( money ) 100 );
    board_addCard( "Speeding fine $15", CARD_CHANCE, PAY,
                   ( union CardParameter ) ( money ) 15, NO_ACTION, noParam );
    board_addCard( "Take a trip to Reading Rainbow. If you pass Go, collect "
                   "$200", CARD_CHANCE, ADVANCE_TO_NAME,
                   ( union CardParameter ) "Reading Rainbow", NO_ACTION, noParam );
    board_addCard( "You have been elected Chairman of the Board. Pay each player "
                   "$50", CARD_CHANCE, PAY_EACH_PLAYER,
                   ( union CardParameter ) ( money ) 50, NO_ACTION, noParam );
    board_addCard( "Your building loan matures. Collect $150", CARD_CHANCE, EARN, 
                   ( union CardParameter ) ( money ) 150, NO_ACTION, noParam );


    board_addCard( "Advance to Go (Collect $200)", CARD_COMMUNITY_CHEST,
                   ADVANCE_TO_TYPE, ( union CardParameter ) ( enum PropType ) GO,
                   NO_ACTION, noParam );
    board_addCard( "Bank error in your favor. Collect $200", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 200, NO_ACTION, noParam );
    board_addCard( "Doctor's fee. Pay $50", CARD_COMMUNITY_CHEST, PAY,
                   ( union CardParameter ) ( money ) 50, NO_ACTION, noParam );
    board_addCard( "From sale of stock you get $50", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 50, NO_ACTION, noParam );
    board_addCard( "Get Out of Jail Free", CARD_COMMUNITY_CHEST, GET_OUT_OF_JAIL,
                    noParam, NO_ACTION, noParam );
    board_addCard( "Go to Jail. Go directly to Jail, do not pass Go, do not "
                   "collect $200", CARD_COMMUNITY_CHEST, GO_TO_JAIL, noParam, NO_ACTION,
                   noParam );
    board_addCard( "Holiday fund matures. Receive $100", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 100, NO_ACTION, noParam );
    board_addCard( "Income tax refund. Collect $20", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 20, NO_ACTION, noParam );
    board_addCard( "It is your birthday. Collect $10 from every player", 
                   CARD_COMMUNITY_CHEST, EARN_FROM_PLAYERS,
                   ( union CardParameter ) ( money ) 10, NO_ACTION, noParam );
    board_addCard( "Life insurance matures. Collect $100", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 100, NO_ACTION, noParam );
    board_addCard( "Pay hospital fees of $100", CARD_COMMUNITY_CHEST, PAY,
                   ( union CardParameter ) ( money ) 100, NO_ACTION, noParam );
    board_addCard( "Pay school fees of $50", CARD_COMMUNITY_CHEST, PAY,
                   ( union CardParameter ) ( money ) 50, NO_ACTION, noParam );
    board_addCard( "Receive $25 consultancy fee", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 25, NO_ACTION, noParam );
    board_addCard( "You are assessed for street repair. $40 per house. $115 "
                   "per hotel", CARD_COMMUNITY_CHEST, REPAIRS,
                   ( union CardParameter ) ( money ) 40, REPAIRS,
                   ( union CardParameter ) ( money ) 115 );
    board_addCard( "You have won second prize in a beauty contest. Collect $10",
                   CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 10, NO_ACTION, noParam );
    board_addCard( "You inherit $100", CARD_COMMUNITY_CHEST, EARN,
                   ( union CardParameter ) ( money ) 100, NO_ACTION, noParam );

    for ( int i = 0; i < 10; ++i ) {
        board_playTurn();
    }

    return 0;
}
