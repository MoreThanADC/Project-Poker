#pragma once

#include "Deck.hpp"

#include <memory>
#include <vector>

class Player {
public:
    Player(const std::shared_ptr<Deck>& deck, const std::string& name, const size_t money)
        : deck_(deck), name_(name), money_(money) {};
        
    void getCardFromDeck();
    void printHand() const;
    void printMoney() const;

    size_t performBlind(size_t valueOfBlind);          // placing a blind bet in the pot (before cards are dealt)

    void fold();                  // abandon the round and lose any coins staked
    void check();                 // waiting, possible only when no one raised the bet
    void call();                  // alignment to the present bet
    void bet(size_t amount);      // the first bet in the round
    void raise(size_t amount);    // increasing the current bet
    void allIn();                 // increasing the current bet by all the money you have

    std::vector<Card> getHand() const { return hand_; }

    void operator+=(const size_t amount);
    void operator-=(const size_t amount);

private:
    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;

    const std::string name_;
    size_t money_;
    bool currentOnSmallBlind_ = false;
};