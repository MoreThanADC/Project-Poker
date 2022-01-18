#include "Table.hpp"

void Table::printTable() const {
    for (const auto& card : table_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

void Table::addCardToTable() {
    table_.push_back(deck_->takeCardFromDeck());
}