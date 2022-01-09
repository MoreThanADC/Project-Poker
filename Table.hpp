#pragma once

#include "Deck.hpp"

#include <memory>
#include <vector>

class Table {
public:
    Table(const std::shared_ptr<Deck>& deck)
        : deck_(std::move(deck)){};

    void performTheFlop();
    void performTheTurnOrTheRiver();
    void printTable() const;

    std::vector<Card> getTable() const { return table_; }

private:
    std::vector<Card> table_;
    std::shared_ptr<Deck> deck_;
};