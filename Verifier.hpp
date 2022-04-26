#pragma once

#include "Card.hpp"

#include <string>
#include <vector>

enum class PokerHand { HIGHCARDS,
                       PAIR,
                       TWOPAIRS,
                       THREEKIND,
                       STRAIGHT,
                       FLUSH,
                       FULLHOUSE,
                       FOURKIND,
                       STRAIGHTFLUSH,
                       ROYALFLUSH };

class Verifier {
public:
    PokerHand detectBestCombination(std::vector<Card>& setOfCards);
    std::string printPokerHand(PokerHand pokerHand);

private:
    bool isAPair(const std::vector<Card>& setOfCards);
    bool areTwoPairs(const std::vector<Card>& setOfCards);
    bool isThreeKind(const std::vector<Card>& setOfCards);
    bool isStraight(std::vector<Card> setOfCards);
    bool isFlush(const std::vector<Card>& setOfCards);
    bool isFullHouse(std::vector<Card> setOfCards);
    bool isFourKind(const std::vector<Card>& setOfCards);
    bool isStraightFlush(std::vector<Card> setOfCards);
    bool isRoyalFlush(const std::vector<Card>& setOfCards);
};
