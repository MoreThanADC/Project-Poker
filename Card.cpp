#include "Card.hpp"

std::string Card::printSuit() const {
    switch(suit_) {
    case (Suit::SPADES)     : return "Spades";
    case (Suit::HEARTS)     : return "Hearts";
    case (Suit::DIAMONDS)   : return "Diamonds";
    case (Suit::CLUBS)      : return "Clubs"; 
    default                 : return "Incorrect suit";
    }
}

std::string Card::printRank() const {
    switch(rank_) {
    case (Rank::ACE)        : return "Ace";
    case (Rank::TWO)        : return "Two";
    case (Rank::THREE)      : return "Three";
    case (Rank::FOUR)       : return "Four";
    case (Rank::FIVE)       : return "Five";
    case (Rank::SIX)        : return "Six";
    case (Rank::SEVEN)      : return "Seven";
    case (Rank::EIGHT)      : return "Eight";
    case (Rank::NINE)       : return "Nine";
    case (Rank::TEN)        : return "Ten";
    case (Rank::JACK)       : return "Jack";
    case (Rank::QUEEN)      : return "Queen";
    case (Rank::KING)       : return "King";
    default                 : return "Incorrect rank";
    }
}