#include "Table.hpp"

void Table::performTheFlop() {
    table_.push_back(deck_->takeCardFromDeck());
    table_.push_back(deck_->takeCardFromDeck());
    table_.push_back(deck_->takeCardFromDeck());
}

void Table::performTheTurnOrRiver() {
    table_.push_back(deck_->takeCardFromDeck());
}

void Table::printTable() const {
    for(const auto& card : table_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}