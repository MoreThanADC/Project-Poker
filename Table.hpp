#pragma once

#include "Deck.hpp"

#include <memory>
#include <vector>

class Table {
public:
    Table(const std::shared_ptr<Deck>& deck)
        : deck_(deck) {};

    void addCardToTable();

    void printTable() const;
    size_t printPool() const;

    std::vector<Card> getTable() const { return table_; }

    void addToPool(const size_t amount);

    std::shared_ptr<Deck> getDeck() { return deck_; }

private:
    std::vector<Card> table_;
    std::shared_ptr<Deck> deck_;
    size_t pool_ = 0;
};