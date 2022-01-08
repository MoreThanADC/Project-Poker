#include <iostream>
#include <memory>

#include "Deck.hpp"
#include "Player.hpp"


int main() {
    Deck deck;
    auto pointerToDeck = std::make_shared<Deck>(deck);
    
    pointerToDeck->setupDeck();
    pointerToDeck->shuffleTheDeck();
  
    std::cout << "\nNUMBER OF CARDS IN THE DECK: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    Player player1(pointerToDeck);
    Player player2(pointerToDeck);
 
    player1.getCardFromDeck();
    player1.getCardFromDeck();

    player2.getCardFromDeck();
    player2.getCardFromDeck();
   
    std::cout << "\nNUMBER OF CARDS: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    
    player1.printHand();
    player2.printHand();
    return 0;
}