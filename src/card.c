#include "card.h"
#include <stdio.h>
#include <stdlib.h>


struct Card* card_createCard( char *title, enum CardAction action1, 
                              union CardParameter parameter1,
                              enum CardAction action2,
                             union CardParameter parameter2 ) {
    struct Card *card = malloc( sizeof( struct Card ) ); 
    card->title = title;
    card->action1 = action1;
    card->parameter1 = parameter1;
    card->action2 = action2;
    card->parameter2 = parameter2;
    return card;
}
