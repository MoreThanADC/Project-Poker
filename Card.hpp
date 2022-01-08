#pragma once

#include <iostream>

enum class Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum class Suit { SPADES, HEARTS, DIAMONDS, CLUBS };

struct Card {
    Card(const Rank& rank, const Suit& suit);
    std::string printSuit() const;
    std::string printRank() const;
    std::string printValue() const;

private:
    Rank rank_;
    Suit suit_;
    int value_;
};