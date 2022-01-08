#include <iostream>
#include <memory>


#include "Player.hpp"
#include "Table.hpp"


int main() {
    Deck deck;
    auto pointerToDeck = std::make_shared<Deck>(deck);
    
    pointerToDeck->setupDeck();
    pointerToDeck->shuffleTheDeck();
  
    std::cout << "\nINITIAL NUMBER OF CARDS IN THE DECK: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    Table table(pointerToDeck);
    Player player1(pointerToDeck);
    Player player2(pointerToDeck);
 
    player1.getCardFromDeck();
    player1.getCardFromDeck();

    player2.getCardFromDeck();
    player2.getCardFromDeck();

    table.performTheFlop();
   
    std::cout << "\nNUMBER OF CARDS AFTER FLOP: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    std::cout << "\nNUMBER OF CARDS AFTER TURN: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    table.performTheTurnOrRiver();
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

     std::cout << "\nNUMBER OF CARDS AFTER RIVER: " << pointerToDeck->cardsInTheDeck() <<  '\n';
    table.performTheTurnOrRiver();
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    return 0;
}