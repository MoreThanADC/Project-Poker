#include "Player.hpp"

void Player::getCardFromDeck() {
    if (hand_.size() < 2) {
        hand_.push_back(deck_->takeCardFromDeck());
    }
}

void Player::returnCardsToDeck() {
    for (auto& card : hand_) {
        deck_->returnCardToDeck(card);
        hand_.pop_back();
    }
}

bool Player::wasBlindCarriedOutCorrectly(size_t valueOfBlind) {
    if (money_ <= valueOfBlind) {
        std::cout << "Player don't have enough money for bet blind\n";
        return false;
    } else {
        money_ -= valueOfBlind;
        table_->addToPool(valueOfBlind);
        return true;
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
    isActiveInRound_ = false;
}

void Player::check() {
    std::cout << "check\n";
}

void Player::call() {
    size_t missingValueToBet = table_->returnCurrentBet() - currentBet_;

    if (missingValueToBet <= 0) {
        std::cout << "you can't beat yourself\n";
    } else if (money_ < missingValueToBet) {
        allIn();
    } else {
        money_ -= missingValueToBet;
        table_->addToPool(missingValueToBet);
        currentBet_ += missingValueToBet;
    }
}

void Player::bet() {
    size_t bet;
    do {
        std::cout << "Money to bet: ";
        std::cin >> bet;
        if (bet > money_) {
            std::cout << "You don't have enough money!\n";
        }
        if (bet < table_->returnCurrentBet()) {
            std::cout << "You'r bet must be bigger than current bet: " << table_->returnCurrentBet() << "\n";
        }
    } while (bet > money_ && bet < table_->returnCurrentBet());
    
    size_t missingValueToBet = table_->returnCurrentBet() - currentBet_;

    money_ -= missingValueToBet;
    table_->addToPool(missingValueToBet);

    std::cout << name_ << " bet: " << bet << ", account balance: " << money_ << '\n';
}

void Player::allIn() {
    if (currentBet_ >= table_->returnCurrentBet()) {
        std::cout << "you can't beat yourself\n";
        return;
    }
    if (money_ > 0) {
        table_->addToPool(money_);
        currentBet_ += money_;
        money_ = 0;
    }
}

void Player::setCurrentBet(size_t value){
    currentBet_ = value;
}

void Player::printHand() const {
    for (const auto& card : hand_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

void Player::printMoney() const {
    std::cout << name_ << " have: " << money_ << '\n';
}
