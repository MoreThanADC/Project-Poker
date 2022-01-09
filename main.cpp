#include <iostream>
#include <memory>

#include "Player.hpp"
#include "Table.hpp"
#include "Verifier.hpp"

int main() {
    Deck deck;
    auto pointerToDeck = std::make_shared<Deck>(deck);

    pointerToDeck->setupDeck();
    pointerToDeck->shuffleTheDeck();

    std::cout << "\nINITIAL NUMBER OF CARDS IN THE DECK: " << pointerToDeck->cardsInTheDeck() << '\n';
    Table table(pointerToDeck);
    Player player1(pointerToDeck);
    Player player2(pointerToDeck);

    player1.getCardFromDeck();
    player1.getCardFromDeck();

    player2.getCardFromDeck();
    player2.getCardFromDeck();

    table.performTheFlop();

    std::cout << "\nNUMBER OF CARDS AFTER FLOP: " << pointerToDeck->cardsInTheDeck() << '\n';
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    std::cout << "\nNUMBER OF CARDS AFTER TURN: " << pointerToDeck->cardsInTheDeck() << '\n';
    table.performTheTurnOrTheRiver();
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    std::cout << "\nNUMBER OF CARDS AFTER RIVER: " << pointerToDeck->cardsInTheDeck() << '\n';
    table.performTheTurnOrTheRiver();
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    std::vector<Card> tableCards = table.getTable();

    std::vector<Card> firstPlayerHand = player1.getHand();
    std::vector<Card> firstPlayerAllCards;
    std::merge(begin(tableCards), end(tableCards), begin(firstPlayerHand), end(firstPlayerHand), std::back_inserter(firstPlayerAllCards));
    std::sort(begin(firstPlayerAllCards), end(firstPlayerAllCards));

    std::vector<Card> secondPlayerHand = player2.getHand();
    std::vector<Card> secondPlayerAllCards;
    std::merge(begin(tableCards), end(tableCards), begin(secondPlayerHand), end(secondPlayerHand), std::back_inserter(secondPlayerAllCards));
    std::sort(begin(secondPlayerAllCards), end(secondPlayerAllCards));

    Verifier verifier;

    std::cout << "\nPlayer 1 PokerHand : " << verifier.printPokerHand(verifier.verify(firstPlayerAllCards));
    std::cout << "\nPlayer 2 PokerHand : " << verifier.printPokerHand(verifier.verify(secondPlayerAllCards));

    std::cout << "\nWHO WON? ";
    verifier.verify(firstPlayerAllCards) > verifier.verify(secondPlayerAllCards) ? std::cout << "PLAYER 1\n" : std::cout << "PLAYER 2\n";

    return 0;
}