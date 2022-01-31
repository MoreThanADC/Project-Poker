#include "Player.hpp"

void Player::getCardFromDeck() {
    hand_.push_back(deck_->takeCardFromDeck());
}

void Player::printHand() const {
    for (const auto& card : hand_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

void Player::printMoney() const {
    std::cout << name_ << " have: " << money_ << '\n';
}

size_t Player::performBlind(size_t valueOfBlind) {
    if (money_ < valueOfBlind) {
        std::cout << "Player don't have enough money for bet blind\n";
        return 0;
    } else {
        money_ -= valueOfBlind;
        return valueOfBlind;
    }
}








void Player::operator+=(const size_t amount) {
    money_ += amount;
}

void Player::operator-=(const size_t amount) {
    if (amount > money_) {
        money_ = 0;
    } else {
        money_ -= amount;
    }
}