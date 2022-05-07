#pragma once

#include "Deck.hpp"

#include <memory>
#include <vector>

class Table {
public:
    Table(const std::shared_ptr<Deck>& deck)
        : deck_(deck) {};

    void addCardToTable();
    void returnCardsToDeck(); 

    void printTable() const;
    size_t returnNumberOfCards() const;


    void addToPool(const size_t amount);
    void setCurrentBet(const size_t highestBet);

    std::vector<std::shared_ptr<Card>> getTable() const { return table_; }
    std::shared_ptr<Deck> getDeck() const { return deck_; }
    size_t returnPool() const { return pool_; }
    size_t returnCurrentBet() const { return currentBet_; }

private:
    std::vector<std::shared_ptr<Card>> table_;
    std::shared_ptr<Deck> deck_;
    size_t pool_ = 0;
    size_t currentBet_ = 0;
};