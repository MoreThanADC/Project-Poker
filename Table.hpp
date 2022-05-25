#ifndef TABLE_HPP
#define TABLE_HPP

#include "Deck.hpp"

#include <memory>
#include <vector>

class Table {
public:
    explicit Table(const std::shared_ptr<Deck>& deck)
        : deck_(deck) {};

    void addCardToTable();
    void returnCardsToDeck(); 

    void printTable() const;
    size_t returnNumberOfCards() const;

    void resetPool();
    void addToPool(const size_t amount);
    void setCurrentBet(const size_t highestBet);

    std::vector<Card> getTable() const { return table_; }
    std::shared_ptr<Deck> getDeck() const { return deck_; }

    size_t getPool() const { return pool_; }
    size_t returnCurrentBet() const { return currentBet_; }

private:
    std::vector<Card> table_;
    std::shared_ptr<Deck> deck_;
    size_t pool_ = 0;
    size_t currentBet_ = 0;
};

#endif