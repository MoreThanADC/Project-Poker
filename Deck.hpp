#pragma once

#include <vector>
#include <iostream>

#include "Card.hpp"

struct Deck {
    void setupDeck();
    void printCards();
    void shuffleTheDeck();

    size_t cardsInTheDeck() { return deck_.size(); }; 
    Card takeCardFromDeck();

private:
    std::vector<Card> deck_;
};