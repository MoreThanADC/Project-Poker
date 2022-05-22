#pragma once

#include <memory>

#include "Comparator.hpp"
#include "Verifier.hpp"
#include "Table.hpp"
#include "Player.hpp"

class Game {
public:
    Game();

    void startGame();

private:
    void selectOperation();
    void printOperations() const;

    void performRound();
    void addPlayer();
    void removePlayer(const std::string& name);
    void removePlayer();
    void printPlayers() const;
    void printWinner();

    void performPlayerAction();
    void performPreFlop();
    void performFlop();
    void performTurnOrTheRiver();

    void prepareDeck();

    void activatePlayers();
    bool arePlayersActive();

    void returnPlayersCards();
    void returnCardsFromTable();

    void displayHandsAndTable() const;

    void prepareCardsForVerdict();
    void setBestCombinations();
    void sortPlayersByHand();

    bool isTieAmongWinners();
    void payOutForWinners();

    std::shared_ptr<Verifier> verifier_;
    std::unique_ptr<Comparator> comparator_;
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Table> table_;
    std::vector<std::shared_ptr<Player>> players_;

    size_t roundNumber_ = 0;
    const size_t valueOfBlind_ = 100;
    size_t maxNumberOfPlayers_ = 8;
};