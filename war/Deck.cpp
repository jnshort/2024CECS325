// Short, Justin
// CECS 325-02
// Program 1: War
// 02/15/2024
#include "Deck.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Construct a Deck with standard 52 cards
Deck::Deck() {
  char ranks[13] = {'2', '3', '4', '5', '6', '7', '8',
                    '9', 'T', 'J', 'Q', 'K', 'A'};
  char suits[4] = {'C', 'D', 'H', 'S'};

  // Create the 52 cards and append each to the vector
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      Card new_card = Card(ranks[i], suits[j]);
      pile.push_back(new_card);
    }
  }
}

// Displays the entire deck at once
// in a user readable format
void Deck::display() {
  // Print 4 lines
  int k = 0;
  for (int i = 1; i < 5; i++) {
    // Print 13 Cards per line
    for (int j = 1; j < 14; j++) {
      pile[k].display();
      k++;
    }
    std::cout << std::endl;
  }
}

// Deal the top card of the deck
// removing it from the deck
Card Deck::deal() {
  Card top_card = pile.back();
  pile.pop_back();
  return top_card;
}

// Shuffle the deck
void Deck::shuffle() {
  // Set random seed using current time
  srand(time(0));

  // Swap 2 random indeces 10000 times
  for (int i = 0; i <= 10000; i++) {
    int position1 = rand() % 52; // random number between 1-51
    int position2 = rand() % 52;

    Card temp = pile[position1];
    pile[position1] = pile[position2];
    pile[position2] = temp;
  }
}
