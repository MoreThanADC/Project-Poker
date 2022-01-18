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

    std::vector<Card> getHand() const { return hand_; }

    void operator+=(const size_t amount);
    void operator-=(const size_t amount);

private:
    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;
    const std::string name_;
    size_t money_;
};