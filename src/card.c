#include "card.h"
#include <stdio.h>
#include <stdlib.h>


struct Card card_createCard( char *title, enum CardAction action1, 
                              union CardParameter parameter1,
                              enum CardAction action2,
                             union CardParameter parameter2 ) {
    return ( struct Card ) { .title = title, 
                             .action1 = action1, 
                             .parameter1 = parameter1,
                             .action2 = action2,
                             .parameter2 = parameter2 };
}
