#pragma once

#include "Deck.hpp"
#include "Table.hpp"
#include "Verifier.hpp"

#include <memory>
#include <vector>

class Player {
public:
    Player(const std::shared_ptr<Deck>& deck, const std::shared_ptr<Table>& table, const std::string& name = "Anonymus", const size_t money = 1000)
        : deck_(deck), table_(table), name_(name), money_(money) {
            //std::cout << "CREATE PLAYER\n";
        };
        
    ~Player() {
        //std::cout << "DESTROY PLAYER\n";
    }
    void getCardFromDeck();
    void returnCardsToDeck();
    
    void printHand() const;
    void printMoney() const;

    bool wasBlindCarriedOutCorrectly(size_t valueOfBlind);        // placing a blind bet in the pot (before cards are dealt)
    void prepareCardsForVerdict();

    bool fold();        // abandon the round and lose any coins staked
    bool check();       // waiting, possible only when no one raised the bet
    bool call();        // alignment to the present bet
    bool bet();         // increasing the current bet
    bool performBet(const size_t bet);
    bool allIn();       // increasing the current bet by all the money you have

    void displayActions();
    void selectActions();

    std::vector<Card> getHand() const { return hand_; }
    std::vector<Card> getHandToEvaluate() const { return handToEvaluate_; }
    std::string getName() const { return name_; }
    size_t getMoney() const { return money_; }
    PokerHand getBestCombination() const { return bestCombination_; }

    size_t returnNumberOfCards() const { return hand_.size(); }
    size_t returnMoney() const { return money_; }
    size_t returnCurrentBet() const { return currentBet_; }

    bool isActiveInRound() const { return isActiveInRound_; }

    void setCurrentBet(const size_t value) { currentBet_ = value; }
    void setName(const std::string& name);
    void setPlayerActivity(const bool isActive) { isActiveInRound_ = isActive; }
    void setBestCombination(const PokerHand& bestCombination) { bestCombination_ = bestCombination; }

private:
    size_t getInputFromUser();

    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Table> table_;

    const std::string name_;
    size_t money_;
    size_t currentBet_ = 0;
    PokerHand bestCombination_ = PokerHand::HIGHCARDS;
    std::vector<Card> handToEvaluate_;

    bool isActiveInRound_ = true;
    bool currentOnSmallBlind_ = false;
};