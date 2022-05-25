#ifndef DECK_HPP
#define DECK_HPP

#include "Card.hpp"

#include <iostream>
#include <memory>
#include <vector>

struct Deck 
{
    Deck();

    void shuffleTheDeck();
    void printCards() const;

    size_t cardsInTheDeck() const { return deck_.size(); }
    std::vector<Card> getDeck() const { return deck_; }

    Card takeCardFromDeck();
    void returnCardToDeck(const Card& card);

private:
    void setupDeck();
    std::vector<Card> deck_;
};

#endif