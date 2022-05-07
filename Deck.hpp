#pragma once

#include "Card.hpp"

#include <iostream>
#include <memory>
#include <vector>

struct Deck {
    Deck();
    ~Deck() {
        std::cout << "DESTROY DECK\n";
    }

    void shuffleTheDeck();
    void printCards();


    size_t cardsInTheDeck() const { return deck_.size(); }
    std::vector<std::shared_ptr<Card>> getDeck() { return deck_; }

    std::shared_ptr<Card> takeCardFromDeck();
    void returnCardToDeck(const std::shared_ptr<Card>& card);

private:
    void setupDeck();
    std::vector<std::shared_ptr<Card>> deck_;
};