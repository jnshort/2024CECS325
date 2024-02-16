// Short, Justin
// CECS 325-02
// Program 1: War
// 02/15/2024

#include "Card.h"
#include "Deck.h"
#include <iostream>
#include <string>

void line_break() {
  std::cout << "*************************************" << std::endl;
}

int main() {
  // Define variables used in main
  std::string player1;
  int p1_score = 0;
  std::string player2;
  int p2_score = 0;
  int ties = 0;

  Deck deck = Deck();

  // Set player names
  std::cout << "War" << std::endl;
  line_break();
  std::cout << "Enter Name of Player 1: ";
  std::cin >> player1;
  std::cout << "Enter Name of Player 2: ";
  std::cin >> player2;

  line_break();
  std::cout << "Original Deck" << std::endl;
  deck.display();

  deck.shuffle();
  line_break();

  std::cout << "Shuffled Deck" << std::endl;
  deck.display();

  for (int i = 0; i < 26; i++) {
    line_break();
    std::cout << "Game " << (i+1) << std::endl;
    // Deal each player a card
    Card p1_card = deck.deal();
    Card p2_card = deck.deal();

    // Display each player's card
    std::cout << "\t" << player1 << ": ";
    p1_card.display();
    std::cout << std::endl;

    std::cout << "\t" << player2 << ": ";
    p2_card.display();
    std::cout << std::endl;

    // Compare cards and display the winner
    int result = p1_card.compare(p2_card);
    if (result == 1) {
      p1_score += 1;
      std::cout << "Winner: " << player1 << std::endl;
    } else if (result == -1) {
      std::cout << "Winner: " << player2 << std::endl;
      p2_score += 1;
    } else {
      std::cout << "Tie Game" << std::endl;
      ties += 1;
    }
  }
  line_break();
  // Display Table of Stats from all 26 games
  std::cout << "\t" << player1 << "\tvs\t" << player2 << std::endl;
  std::cout << "Wins\t" << p1_score << "\t\t" << p2_score << std::endl;
  std::cout << "Losses\t" << (26 - (p1_score + ties)) << "\t\t" << (26 - (p2_score + ties))
            << std::endl;
  std::cout << "Ties\t\t" << ties << std::endl;
}
