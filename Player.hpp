#pragma once

#include "Deck.hpp"

#include <memory>
#include <vector>

class Player {
public:
    Player(const std::shared_ptr<Deck>& deck, const size_t money = 1000)
        : deck_(std::move(deck)), money_(money) {};
        
    void getCardFromDeck();
    void printHand() const;

    std::vector<Card> getHand() const { return hand_; }

private:
    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;
    size_t money_;
};