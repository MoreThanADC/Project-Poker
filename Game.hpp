#pragma once

#include <memory>

#include "Comparator.hpp"
#include "Verifier.hpp"
#include "Table.hpp"
#include "Player.hpp"

class Game {
public:
    Game(std::unique_ptr<Comparator>&& comparator, Table& table, std::vector<Player>& players) : 
       comparator_(std::move(comparator)), table_(table), players_(players) {}

    bool isPlayerWinner(std::vector<Card>& firstHand, std::vector<Card>& secondHand);

    void performPreFlop();
    void performFlop();
    void performTurnOrTheRiver();

private:
    std::unique_ptr<Comparator> comparator_;
    Table& table_;
    std::vector<Player>& players_;
};