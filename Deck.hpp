#pragma once

#include "Card.hpp"

#include <iostream>
#include <vector>

struct Deck {
    void setupDeck();
    void printCards();
    void shuffleTheDeck();

    size_t cardsInTheDeck() const { return deck_.size(); }
    std::vector<Card> getDeck() { return deck_; }

    Card takeCardFromDeck();
    void returnCardToDeck(const Card& card);

private:
    std::vector<Card> deck_;
};