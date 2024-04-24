// Short, Justin
// CECS 325-02
// Program 2: More War
// Due Date: 02/27/2024
//
// I certify that this program is my own original work. I did not copy this
// program from any other source. I further certify that I typed each and every
// line of code in this program.

#include <ctime>
#include <iostream>
#include <ostream>
#include <string>

// Declare Classes so i can use them
// Methods are below main
class Card {
public:
  char rank;
  char suit;

public:
  void display();
  int compare(Card);
  Card();
  Card(char, char);
};

class Deck {
private:
  Card pile[52];
  int top = 0;

public:
  Deck();
  Card deal();
  void display();
  void shuffle();
  bool isEmpty();
};

// Line Break Function
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

  std::string num_games;
  std::cout << "Enter Number of Games: ";
  std::cin >> num_games;

  int games = stoi(num_games);

  line_break();
  std::cout << "Original Deck" << std::endl;
  deck.display();

  deck.shuffle();
  line_break();

  std::cout << "Shuffled Deck" << std::endl;
  deck.display();

  for (int i = 0; i < games; i++) {
    line_break();
    std::cout << "Game " << (i + 1) << std::endl;
    // Deal each player a card

    Card p1_card;
    Card p2_card;
    try {
      p1_card = deck.deal();
    } catch (char error) {
      deck.shuffle();
      p1_card = deck.deal();
      std::cout << "Deck empty, shuffling" << std::endl;
    }
    try {
      p2_card = deck.deal();
    } catch (char error) {
      deck.shuffle();
      p2_card = deck.deal();
      std::cout << "Deck empty, shuffling" << std::endl;
    }

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
  // Display Table of Stats from all games
  std::cout << "Final Scores" << std::endl;
  std::cout << "\t" << player1 << "\tvs\t" << player2 << std::endl;
  std::cout << "Wins\t" << p1_score << "\t\t" << p2_score << std::endl;
  std::cout << "Losses\t" << (games - (p1_score + ties)) << "\t\t"
            << (games - (p2_score + ties)) << std::endl;
  std::cout << "Ties\t\t" << ties << std::endl;
}

// Card Constructor
Card::Card() {
  rank = 'U';
  suit = 'U';
}

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
// Construct a Deck with standard 52 cards
Deck::Deck() {
  char ranks[13] = {'2', '3', '4', '5', '6', '7', '8',
                    '9', 'T', 'J', 'Q', 'K', 'A'};
  char suits[4] = {'C', 'D', 'H', 'S'};

  // create the 52 cards and append each to the vector
  int k = 0;
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      Card new_card = Card(ranks[i], suits[j]);
      pile[k] = new_card;
      k++;
    }
  }
}

// Returns true of the deck is empty
// otherwise returns false
bool Deck::isEmpty() { return (top == 52); }

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
// update index of top
Card Deck::deal() {
  if (isEmpty()) {
    top = 0;    // Reset top of pile
    throw('e'); // Throw error so main knows to shuffle
  }
  Card top_card = pile[top];
  top++;
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
