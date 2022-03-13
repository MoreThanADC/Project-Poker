#pragma once

#include <memory>

#include "Comparator.hpp"
#include "Verifier.hpp"
#include "Table.hpp"
#include "Player.hpp"

class Game {
public:
    Game(std::unique_ptr<Comparator>&& comparator, Table& table, std::vector<std::shared_ptr<Player>>& players) : 
       comparator_(std::move(comparator)), table_(table), players_(players) {}

    void performRound();
    void addPlayer();

    bool isPlayerWinner(std::vector<Card>& firstHand, std::vector<Card>& secondHand);

private:
    void performPlayerAction();
    void performPreFlop();
    void performFlop();
    void performTurnOrTheRiver();

    void displayMoneyAndPool() const;
    void displayHandsAndTable() const;

    std::unique_ptr<Comparator> comparator_;
    Table& table_;
    std::vector<std::shared_ptr<Player>> players_;

    size_t roundNumber_ = 0;
    const size_t valueOfBlind_ = 100;
};