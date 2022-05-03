#pragma once

#include "Card.hpp"

#include <iostream>
#include <vector>

struct Deck {
    Deck();

    void shuffleTheDeck();
    void printCards();


    size_t cardsInTheDeck() const { return deck_.size(); }
    std::vector<Card> getDeck() { return deck_; }

    Card takeCardFromDeck();
    void returnCardToDeck(const Card& card);

private:
    void setupDeck();
    std::vector<Card> deck_;
};