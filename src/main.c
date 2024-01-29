#include "board.h"
#include "tile.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv ) {
    printf( "Working\n" );

    board_initialize( 4 );
    board_addTile( "GO", 0, 0, GO, 99 );
    board_addTile( "Mediterranean Avenue", 60, 30, PROPERTY, 0);
    board_addTile( "Community Chest", 0, 0, COMMUNITY_CHEST, 0);
    board_addTile( "Baltic Avenue", 60, 30, PROPERTY, 100);
    board_addTile( "Income Tax", 200, 0, TAX, 101);
    board_addTile( "Reading Railroad", 200, 25, RAILROAD, 1);
    board_addTile( "Oriental Avenue", 100, 50, PROPERTY, 2);
    board_addTile( "Vermont Avenue", 100, 50, PROPERTY, 2);
    board_addTile( "Conneticut Avenue", 120, 60, PROPERTY, 2);
    board_addTile( "Jail", 0, 0, JAIL, 102 );


    for ( int i = 0; i < 10; ++i ) {
        board_playTurn();
    }

    return 0;
}
