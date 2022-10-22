#include "Player.hpp"
#include "Helpers.hpp"

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
    for (const auto& card : hand_)
    {
        deck_->returnCardToDeck(card);
        hand_.pop_back();
    }
}

void Player::addToAccount(const size_t money)
{
    money_ += money;
}

void Player::performBlind(const size_t valueOfBlind)
{
    money_ -= valueOfBlind;
    table_->addToPool(valueOfBlind);
}

void Player::prepareCardsForVerdict()
{
    size_t MAX_NUMBER_OF_CARDS = 7;
    handToEvaluate_.clear();
    handToEvaluate_.reserve(MAX_NUMBER_OF_CARDS);

    std::vector<Card> table = table_->getTable();

    std::ranges::sort(hand_, helpers::sortDescending);
    std::ranges::sort(table, helpers::sortDescending);

    std::ranges::merge(hand_, table, std::back_inserter(handToEvaluate_));
}

void Player::displayActions() const
{
    std::cout << '\n' << name_ << '\n';
    std::cout << "1 - Fold - abandon the round and lose all coins staked\n";
    std::cout << "2 - Check - waiting, possible only when no one raised the bet\n";
    std::cout << "3 - Call - alignment to the present bet\n";
    std::cout << "4 - Bet - increasing the current bet\n";
    std::cout << "5 - All-In - bet all of your money\n";  
    std::cout << "Select action: ";
}

void Player::selectActions() 
{
    size_t choice = 0;
    bool isActionFinished = false;
    do 
    {
        displayActions();
        std::cin >> choice;
        switch(choice)
        {
        case 1 : isActionFinished = fold();
            break;
        case 2 : isActionFinished = check();
            break;
        case 3 : isActionFinished = call();
            break;
        case 4 : isActionFinished = bet();
            break;
        case 5 : isActionFinished = allIn();
            break;
        default : std::cout << "Wrong choice, try again.\n";
        }
    }
    while (choice < 1 || choice > 5 || !isActionFinished);
}

bool Player::fold()
{
    isActiveInRound_ = false;
    return true;
}

bool Player::check() const
{
    if (table_->getCurrentBet() != currentBet_)
    {
        std::cout << "You can't check, your bet is lower than current bet on the table.\n";
        return false;
    }

    return true;
}

bool Player::call()
{
    size_t missingValueToBet = table_->getCurrentBet() - currentBet_;

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
    if (bet <= table_->getCurrentBet())
    {
        std::cout << "You'r bet must be bigger than current bet: " << table_->getCurrentBet() << "\n";
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
    if (currentBet_ >= table_->getCurrentBet())
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
