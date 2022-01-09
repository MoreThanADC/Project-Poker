#pragma once

#include <vector>
#include "Card.hpp"

enum class PokerHand { HIGHCARDS, PAIR, TWOPAIRS, THREEKIND, STRAIGHT, FLUSH, FULLHUOSE, FOURKIND, STRAIGHTFLUSH, ROYALFLUSH };

class Verifier {
public:
    PokerHand verify(std::vector<Card>& setOfCards);

    bool isAPair(std::vector<Card>& setOfCards);
    bool areTwoPairs(std::vector<Card>& setOfCards);
    bool isThreeKind(std::vector<Card>& setOfCards);
    bool isStraight(const std::vector<Card>& setOfCards);
    bool isFlush(const std::vector<Card>& setOfCards);
    bool isFullHouse(const std::vector<Card>& setOfCards);
    bool isFourKind(std::vector<Card>& setOfCards);
    bool isStraightFlush(const std::vector<Card>& setOfCards);
    bool isRoyalFlush(const std::vector<Card>& setOfCards);
    std::vector<int> highCards(const std::vector<Card>& setOfCards);
};