#pragma once

#include "Card.hpp"

#include <iostream>
#include <vector>

struct Deck {
    void setupDeck();
    void printCards();
    void shuffleTheDeck();

    size_t cardsInTheDeck() const { return deck_.size(); }

    Card takeCardFromDeck();
    void returnCardToDeck(const Card& card);

private:
    std::vector<Card> deck_;
};