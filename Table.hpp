#pragma once

#include <vector>
#include <memory>

#include "Deck.hpp"

class Table {
public:
    Table(const std::shared_ptr<Deck>& deck) : deck_(std::move(deck)) {};
    void performTheFlop();
    void performTheTurnOrRiver();
    void printTable() const;
private:
    std::vector<Card> table_;
    std::shared_ptr<Deck> deck_;

};