#pragma once

#include <vector>
#include "Card.hpp"

enum class PokerHand { HIGHCARDS, PAIR, TWOPAIRS, THREEKIND, STRAIGHT, FLUSH, FULLHUOSE, FOURKIND, POKER };

class Verifier {
public:
    PokerHand verify(const std::vector<Card>& setOfCards);

private:
    bool isAPair(const std::vector<Card>& setOfCards);
    bool areTwoPairs(const std::vector<Card>& setOfCards);
    bool isThreeKind(const std::vector<Card>& setOfCards);
    bool isStraight(const std::vector<Card>& setOfCards);
    bool isFlush(const std::vector<Card>& setOfCards);
    bool isFullHouse(const std::vector<Card>& setOfCards);
    bool isFourKind(const std::vector<Card>& setOfCards);
    bool isPoker(const std::vector<Card>& setOfCards);
    std::vector<int> highCards(const std::vector<Card>& setOfCards);
};