#include "Table.hpp"

void Table::printTable() const {
    for (const auto& card : table_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

size_t Table::printPool() const {
    return pool_;
}

void Table::addCardToTable() {
    table_.push_back(deck_->takeCardFromDeck());
}

void Table::addToPool(const size_t amount) {
    pool_ += amount;
}