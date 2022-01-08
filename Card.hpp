#pragma once

#include <iostream>

enum class Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum class Suit { SPADES, HEARTS, DIAMONDS, CLUBS };

struct Card {
    Card(Rank rank, Suit suit) : rank_(rank), suit_(suit) {};
private:
    Rank rank_;
    Suit suit_;
    int value_;
};