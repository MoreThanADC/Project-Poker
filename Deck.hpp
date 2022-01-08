#pragma once

#include <vector>
#include <iostream>

#include "Card.hpp"

struct Deck {
    void setupDeck();
    std::vector<Card> deck_;

};