#pragma once

#include <vector>
#include <iostream>

#include "Card.hpp"

struct Deck {
    void setupDeck();
    void printCards();
    void shuffleTheDeck();
private:
    std::vector<Card> deck_;
};