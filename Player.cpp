#include "Player.hpp"

#include <algorithm>

void Player::getCardFromDeck()
{
    if (hand_.size() < 2)
    {
        hand_.push_back(deck_->takeCardFromDeck());
    }
}

void Player::returnCardsToDeck()
{
    for (auto& card : hand_)
    {
        deck_->returnCardToDeck(card);
        hand_.pop_back();
    }
}

void Player::addToAccount(const size_t money)
{
    money_ += money;
}

bool Player::wasBlindCarriedOutCorrectly(size_t valueOfBlind)
{
    if (money_ <= valueOfBlind)
    {
        std::cout << "Player don't have enough money for bet blind\n";
        return false;
    }
    else
    {
        money_ -= valueOfBlind;
        table_->addToPool(valueOfBlind);
        return true;
    }
}

void Player::prepareCardsForVerdict()
{
    handToEvaluate_.clear();
    handToEvaluate_.reserve(7);

    std::vector<Card> table = table_->getTable();

    std::sort(begin(hand_), end(hand_));
    std::sort(begin(table), end(table));

    std::merge(hand_.begin(), hand_.end(), table.begin(), table.end(), std::back_inserter(handToEvaluate_));
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
    do 
    {
        std::cin >> choice;
        switch(choice)
        {
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

bool Player::fold()
{
    isActiveInRound_ = false;
    return true;
}

bool Player::check()
{
    if (table_->returnCurrentBet() != currentBet_)
    {
        std::cout << "You can't check, your bet is lower than current bet on the table.\n";
        return false;
    }

    return true;
}

bool Player::call()
{
    size_t missingValueToBet = table_->returnCurrentBet() - currentBet_;

    if (missingValueToBet <= 0)
    {
        std::cout << "you can't beat yourself\n";
        return false;
    } 
    else if (money_ < missingValueToBet)
    {
        allIn();
    }
    else
    {
        money_ -= missingValueToBet;
        table_->addToPool(missingValueToBet);
        currentBet_ += missingValueToBet;
    }

    return true;
}

bool Player::bet()
{
    size_t bet;
    std::cout << "Money to bet: ";
    std::cin >> bet;

    return performBet(bet);
}

bool Player::performBet(const size_t bet) 
{
    if (bet > money_)
    {
        std::cout << "You don't have enough money!\n";
        return false;
    }
    if (bet < table_->returnCurrentBet())
    {
        std::cout << "You'r bet must be bigger than current bet: " << table_->returnCurrentBet() << "\n";
        return false;
    }
    
    size_t missingValueToBet = bet - currentBet_;

    money_ -= missingValueToBet;
    table_->addToPool(missingValueToBet);

    table_->setCurrentBet(bet);
    currentBet_ = bet;

    return true;
}

bool Player::allIn()
{
    if (currentBet_ >= table_->returnCurrentBet())
    {
        std::cout << "you can't bet yourself\n";
        return false;
    }
    if (money_ == 0)
    {
        std::cout << "you don't have money\n";
        return false;
    }

    table_->addToPool(money_);
    currentBet_ += money_;
    money_ = 0;

    return true;
}

void Player::printHand() const 
{
    for (const auto& card : hand_)
    {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

void Player::printMoney() const 
{
    std::cout << name_ << " have: " << money_ << '\n';
}
