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

void Player::displayActions() {
    std::cout << '\n' << name_ << '\n';
    std::cout << "1 - Fold - abandon the round and lose any coins staked\n";
    std::cout << "2 - Check - waiting, possible only when no one raised the bet\n";
    std::cout << "3 - Call - alignment to the present bet\n";
    std::cout << "4 - Bet - the first bet in the round\n";
    std::cout << "5 - Raise - increasing the current bet\n";
    std::cout << "6 - All-In - bet all of your money\n";  
    std::cout << "Select action: ";
}

void Player::selectActions() {
    int number = 0;
    do {
        std::cin >> number;
        if (isdigit(number)) {
            switch(number) {
            case 1 : fold();
                break;
            case 2 : check();
                break;
            case 3 : call();
                break;
            case 4 : bet();
                break;
            case 5 : raise();
                break;
            case 6 : allIn();
                break;
            default : std::cout << "Wrong choice, try again.\n";
            }
        }
    }
    while (number < 1 || number > 6 );
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

void Player::fold() {
    std::cout << "fold\n";
}

void Player::check() {
    std::cout << "check\n";
}

void Player::call() {
    std::cout << "call\n";
}

void Player::bet()  {
    std::cout << "bet\n";
}

void Player::raise() {
    std::cout << "raise\n";
}

void Player::allIn() {
    std::cout << "allIn\n";
}
