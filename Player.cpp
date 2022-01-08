#include "Player.hpp"

void Player::getCardFromDeck() {
    hand_.push_back(deck_->takeCardFromDeck());
};

void Player::printHand() const {
    for(const auto& card : hand_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }

}