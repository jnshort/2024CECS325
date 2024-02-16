// Short, Justin
// CECS 325-02
// Program 1: War
// 02/15/2024
#ifndef xCARD_H
#define xCARD_H


class Card {
    public:
        char rank;
        char suit;

    public:
        Card(char, char);
        void display();
        int compare(Card);
};
#endif
