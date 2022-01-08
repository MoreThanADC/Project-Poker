#pragma once

#include "Deck.hpp"

#include <vector>
#include <memory>

class Player {
public:
    Player(const std::shared_ptr<Deck>& deck) : deck_(std::move(deck)) {};
    void getCardFromDeck();
    void printHand() const;

private:
    std::vector<Card> hand_;
    std::shared_ptr<Deck> deck_;

};