#include "Player.hpp"
#include "Game.hpp"
#include "Table.hpp"
#include "Verifier.hpp"

#include <iostream>
#include <memory>
#include <vector>

int main() {
    Comparator comparator(std::make_shared<Verifier>());
    
    Deck deck;
    auto pointerToDeck = std::make_shared<Deck>(deck);

    pointerToDeck->setupDeck();
    pointerToDeck->shuffleTheDeck();
   
    std::cout << "\nINITIAL NUMBER OF CARDS IN THE DECK: " << pointerToDeck->cardsInTheDeck() << '\n';
    Table table(pointerToDeck);

    
    Player player1(pointerToDeck, "Artur", 2000);
    Player player2(pointerToDeck, "Computer", 3000);

    std::vector<Player> players;
    players.push_back(player1);
    players.push_back(player2);


    Game game(std::make_unique<Comparator>(comparator), table, players);
    player1.printMoney();
    player2.printMoney();

    game.performPreFlop();
    std::cout << "\nNUMBER OF CARDS AFTER PREFLOP: " << pointerToDeck->cardsInTheDeck() << '\n';
    game.performFlop();

    std::cout << "\nNUMBER OF CARDS AFTER FLOP: " << pointerToDeck->cardsInTheDeck() << '\n';
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    players[0].printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    game.performTurnOrTheRiver();
    std::cout << "\nNUMBER OF CARDS AFTER TURN: " << pointerToDeck->cardsInTheDeck() << '\n';
    std::cout << "\nFIRST PLAYER HAND: \n";
    player1.printHand();
    std::cout << "\nSECOND PLAYER HAND: \n";
    player2.printHand();
    std::cout << "\nCARDS ON THE TABLE: \n";
    table.printTable();

    game.performTurnOrTheRiver();
    std::cout << "\nNUMBER OF CARDS AFTER RIVER: " << pointerToDeck->cardsInTheDeck() << '\n';
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

    std::cout << "\nPlayer 1 PokerHand : " << verifier.printPokerHand(verifier.detectBestCombination(firstPlayerAllCards));
    std::cout << "Player 2 PokerHand : " << verifier.printPokerHand(verifier.detectBestCombination(secondPlayerAllCards));

  
    game.isPlayerWinner(firstPlayerAllCards, secondPlayerAllCards) ? std::cout << "\n\nWON PLAYER 1\n" : std::cout << "\n\nWON PLAYER 2\n";

    return 0;
}