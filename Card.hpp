#pragma once

#include <iostream>

enum class Rank { ACE = 1,
                  TWO,
                  THREE,
                  FOUR,
                  FIVE,
                  SIX,
                  SEVEN,
                  EIGHT,
                  NINE,
                  TEN,
                  JACK,
                  QUEEN,
                  KING };
                  
enum class Suit { SPADES,
                  HEARTS,
                  DIAMONDS,
                  CLUBS };

struct Card {
    Card() = default;
    Card(const Rank& rank, const Suit& suit);

    std::string printSuit() const;
    std::string printRank() const;
    std::string printValue() const;

    Suit getSuit() const { return suit_; }
    Rank getRank() const { return rank_; }
    int getValue() const { return value_; }
    void setValue(int newValue) { value_ = newValue; }

    bool operator==(const Card& rhs) {
        return value_ == rhs.getValue();
    }

    bool operator<(Card& rhs) const {
        return value_ < rhs.getValue();
    }

private:
    Rank rank_;
    Suit suit_;
    int value_;
};
