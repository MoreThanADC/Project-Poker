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
   
    Table table(pointerToDeck);

    std::shared_ptr<Player> player1 = std::make_shared<Player>(pointerToDeck, "Artur", 2000);
    std::shared_ptr<Player> player2 = std::make_shared<Player>(pointerToDeck, "Computer", 3000);

    std::vector<std::shared_ptr<Player>> players;

    players.push_back(player1);
    players.push_back(player2);

    Game game(std::make_unique<Comparator>(comparator), table, players);

    game.startGame();

    std::vector<Card> tableCards = table.getTable();

    std::vector<Card> firstPlayerHand = player1->getHand();
    std::vector<Card> firstPlayerAllCards;
    std::merge(begin(tableCards), end(tableCards), begin(firstPlayerHand), end(firstPlayerHand), std::back_inserter(firstPlayerAllCards));
    std::sort(begin(firstPlayerAllCards), end(firstPlayerAllCards));

    std::vector<Card> secondPlayerHand = player2->getHand();
    std::vector<Card> secondPlayerAllCards;
    std::merge(begin(tableCards), end(tableCards), begin(secondPlayerHand), end(secondPlayerHand), std::back_inserter(secondPlayerAllCards));
    std::sort(begin(secondPlayerAllCards), end(secondPlayerAllCards));

    Verifier verifier;

    std::cout << "\nPlayer 1 PokerHand : " << verifier.printPokerHand(verifier.detectBestCombination(firstPlayerAllCards));
    std::cout << "Player 2 PokerHand : " << verifier.printPokerHand(verifier.detectBestCombination(secondPlayerAllCards));

    game.isPlayerWinner(firstPlayerAllCards, secondPlayerAllCards) ? std::cout << "\nWON PLAYER 1\n" : std::cout << "\nWON PLAYER 2\n";

    return 0;
}