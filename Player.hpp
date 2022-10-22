#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Deck.hpp"
#include "Table.hpp"
#include "Verifier.hpp"

#include <memory>
#include <vector>

class Player 
{
public:
    Player(const std::shared_ptr<Deck>& deck, const std::shared_ptr<Table>& table, const std::string& name = "Anonymous", const size_t money = 1000)
        : deck_(deck), table_(table), name_(name), money_(money) {};

    void getCardFromDeck();
    void returnCardsToDeck();
    
    void printHand() const;

    void performBlind(const size_t valueOfBlind);  // placing a blind bet in the pot (before cards are dealt)
    void prepareCardsForVerdict();

    bool fold();        // abandon the round and lose any coins staked
    bool check() const;       // waiting, possible only when no one raised the bet
    bool call();        // alignment to the present bet
    bool bet();         // increasing the current bet
    bool performBet(const size_t bet);
    bool allIn();       // increasing the current bet by all the money you have

    void displayActions() const;
    void selectActions();

    std::vector<Card> getHand() const { return hand_; }
    std::vector<Card> getHandToEvaluate() const { return handToEvaluate_; }
    std::string getName() const { return name_; }
    size_t getMoney() const { return money_; }
    PokerHand getBestCombination() const { return bestCombination_; }
    size_t getNumberOfCards() const { return hand_.size(); }
    size_t getCurrentBet() const { return currentBet_; }

    bool isActiveInRound() const { return isActiveInRound_; }

    void setCurrentBet(const size_t value) { currentBet_ = value; }
    void setPlayerActivity(const bool isActive) { isActiveInRound_ = isActive; }
    void setBestCombination(const PokerHand& bestCombination) { bestCombination_ = bestCombination; }

    void addToAccount(const size_t money);

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
};

#endif