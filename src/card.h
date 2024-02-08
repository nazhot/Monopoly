#ifndef CARD_H
#define CARD_H


#include "tile.h"
enum CardAction {
    NO_ACTION,
    ADVANCE_TO_NAME,
    ADVANCE_TO_TYPE,
    ADVANCE_TO_NAME_PAY_DOUBLE,
    ADVANCE_TO_TYPE_PAY_DOUBLE,
    EARN,
    EARN_FROM_PLAYERS,
    GET_OUT_OF_JAIL,
    GO_BACK,
    GO_TO_JAIL,
    REPAIRS,
    PAY,
    PAY_EACH_PLAYER
};

union CardParameter {
    money money;
    char *locationName;
    enum PropType propertyType;
};

struct Card {
    char *title;
    enum CardAction action1;
    union CardParameter parameter1;
    enum CardAction action2;
    union CardParameter parameter2;
};

struct Card* card_createCard( char *title, enum CardAction action1, 
                              union CardParameter parameter1,
                              enum CardAction action2,
                              union CardParameter parameter2 );

#endif
