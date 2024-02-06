#ifndef CARD_H
#define CARD_H


#include "tile.h"
enum CardAction {
    ADVANCE_TO,
    ADVANCE_TO_PAY_DOUBLE,
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
    PropType propertyType;
};

struct Card {
   enum CardAction action;
   

};

#endif
