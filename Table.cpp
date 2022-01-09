#include "Table.hpp"

void Table::performTheFlop() {
    for (int i = 0; i < 3; i++) {
        table_.push_back(deck_->takeCardFromDeck());
    }
}

void Table::performTheTurnOrTheRiver() {
    table_.push_back(deck_->takeCardFromDeck());
}

void Table::printTable() const {
    for (const auto& card : table_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}