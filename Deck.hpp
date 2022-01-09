#pragma once

#include <iostream>
#include <vector>

#include "Card.hpp"

struct Deck {
    void setupDeck();
    void printCards();
    void shuffleTheDeck();

    size_t cardsInTheDeck() const { return deck_.size(); };
    Card takeCardFromDeck();

private:
    std::vector<Card> deck_;
};