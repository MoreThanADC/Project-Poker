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
    //Card();
    ~Card() {
        std::cout << "DESTROY CARD\n";
    }

    Card(const Rank& rank, const Suit& suit);

    std::string printSuit() const;
    std::string printRank() const;
    std::string printValue() const;

    Suit getSuit() const { return suit_; }
    Rank getRank() const { return rank_; }
    int getValue() const { return value_; }
    void setValue(const int newValue) { value_ = newValue; }

// in the future spaceship operator
    bool operator==(const Card& rhs) const {
        return value_ == rhs.getValue();
    }

    bool operator<(Card& rhs) const {
        return value_ < rhs.getValue();
    }

    bool operator>(Card& rhs) const {
        return value_ > rhs.getValue();
    }

private:
    void setValueForCard(const Rank& rank);

    Rank rank_;
    Suit suit_;
    int value_;
};
