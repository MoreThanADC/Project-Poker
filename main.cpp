#include <iostream>

#include "Deck.hpp"


int main() {
    Deck deck;
    deck.setupDeck();
    deck.printCards();
    deck.shuffleTheDeck();
    std::cout << "\nAFTER SHUFFLE: \n";
    deck.printCards();
    return 0;
}