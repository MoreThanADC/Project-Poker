#include "Table.hpp"

void Table::addCardToTable() {
    if (table_.size() < 5) {
        table_.push_back(deck_->takeCardFromDeck());
    }
}

void Table::returnCardsToDeck() {
    for (auto& card : table_) {
        deck_->returnCardToDeck(card);
        table_.pop_back();
    }
}

size_t Table::returnNumberOfCards() const {
    return table_.size();
}

void Table::addToPool(const size_t amount) {
    pool_ += amount;
}

void Table::printTable() const {
    for (const auto& card : table_) {
        std::cout << card->printRank() << " of " << card->printSuit() << " value : " << card->printValue() << '\n';
    }
}

void Table::setCurrentBet(const size_t highestBet) {
    currentBet_ = highestBet;
}

