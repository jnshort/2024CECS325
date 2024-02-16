// Short, Justin
// CECS 325-02
// Program 1: War
// 02/15/2024
#ifndef xDECK_H
#define xDECK_H

#include <vector>
#include "Card.h"

class Deck {
    private:
        std::vector<Card> pile;
    public:
        Deck();
        Card deal();
        void display();
        void shuffle();
};
#endif
