// Short, Justin
// CECS 325-02
// Program 1: War
// 02/15/2024

#include "Card.h"
#include <iostream>

// Card Constructor
Card::Card(char rnk, char st) {
  rank = rnk;
  suit = st;
}

// Display a card
// cout rank and suit, does not add /n char
void Card::display() {
  if (rank == 'T') {
    std::cout << "10";
  } else {
    std::cout << rank;
  }
  std::cout << suit << " ";
}

// Compare THIS card to another
// Returns result relative to THIS card
int Card::compare(Card c) {
  char rank_array[13] = {'2', '3', '4', '5', '6', '7', '8',
                         '9', 'T', 'J', 'Q', 'K', 'A'};

  int self_index;
  int other_index;

  // Find index of character in array for each card
  for (int i = 0; i < 13; i++) {
    if (rank == rank_array[i])
      self_index = i;
    if (c.rank == rank_array[i])
      other_index = i;
  }
  // Compare by the indeces to find winner
  if (self_index > other_index)
    return 1;
  else if (self_index < other_index)
    return -1;
  else
    return 0;
}
