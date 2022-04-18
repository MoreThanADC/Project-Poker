#include "Player.hpp"

void Player::getCardFromDeck() {
    hand_.push_back(deck_->takeCardFromDeck());
}

void Player::returnCardsToDeck() {
    for (auto& card : hand_) {
        deck_->returnCardToDeck(card);
        hand_.pop_back();
    }
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
    std::cout << "1 - Fold - abandon the round and lose all coins staked\n";
    std::cout << "2 - Check - waiting, possible only when no one raised the bet\n";
    std::cout << "3 - Call - alignment to the present bet\n";
    std::cout << "4 - Bet - increasing the current bet\n";
    std::cout << "5 - All-In - bet all of your money\n";  
    std::cout << "Select action: ";
}

void Player::selectActions() {
    int choice = 0;
    do {
        std::cin >> choice;
        switch(choice) {
            case 1 : fold();
                break;
            case 2 : check();
                break;
            case 3 : call();
                break;
            case 4 : bet();
                break;
            case 5 : allIn();
                break;
            default : std::cout << "Wrong choice, try again.\n";
            }
    }
    while (choice < 1 || choice > 5 );
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
    size_t bet;
    do {
        std::cout << "Money to bet: ";
        std::cin >> bet;
        if (bet > money_) {
            std::cout << "You don't have enough money!\n";
        }
    } while (bet > money_);
    
    money_ -= bet;
    std::cout << name_ << " bet: " << bet << ", account balance: " << money_ << '\n';
}

void Player::allIn() {
    std::cout << "allIn\n";
}
