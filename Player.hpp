#pragma once

#include "Deck.hpp"
#include "Table.hpp"

#include <memory>
#include <vector>

class Player {
public:
    Player(const std::shared_ptr<Deck>& deck, const std::shared_ptr<Table>& table, const std::string& name = "Anonymus", const size_t money = 1000)
        : deck_(deck), table_(table), name_(name), money_(money) {};
        
    void getCardFromDeck();
    void returnCardsToDeck();
    
    void printHand() const;
    void printMoney() const;

    bool wasBlindCarriedOutCorrectly(size_t valueOfBlind);        // placing a blind bet in the pot (before cards are dealt)

    void fold();        // abandon the round and lose any coins staked
    void check();       // waiting, possible only when no one raised the bet
    void call();        // alignment to the present bet
    void bet();         // increasing the current bet
    void allIn();       // increasing the current bet by all the money you have

    void displayActions();
    void selectActions();

    std::vector<Card> getHand() const { return hand_; }
    std::string getName() const { return name_; }

    size_t returnNumberOfCards() const { return hand_.size(); }
    size_t returnMoney() const { return money_; }
    size_t returnCurrentBet() const { return currentBet_; }
    bool isActiveInRound() const { return isActiveInRound_; }

    void setCurrentBet(size_t value);
    void setName(std::string name);

private:
    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Table> table_;

    const std::string name_;
    size_t money_;
    size_t currentBet_ = 0;

    bool isActiveInRound_ = true;
    bool currentOnSmallBlind_ = false;
};