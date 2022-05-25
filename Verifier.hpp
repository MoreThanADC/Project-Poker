#ifndef VERIFIER_HPP
#define VERIFIER_HPP

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
    PokerHand detectBestCombination(std::vector<Card> setOfCards) const;
    std::string printPokerHand(const PokerHand& pokerHand) const;

private:
    bool isAPair(const std::vector<Card>& setOfCards) const;
    bool areTwoPairs(const std::vector<Card>& setOfCards) const;
    bool isThreeKind(const std::vector<Card>& setOfCards) const;
    bool isStraight(const std::vector<Card>& setOfCards) const;
    bool isFlush(const std::vector<Card>& setOfCards) const;
    bool isFullHouse(const std::vector<Card>& setOfCards) const;
    bool isFourKind(const std::vector<Card>& setOfCards) const;
    bool isStraightFlush(const std::vector<Card>& setOfCards) const;
    bool isRoyalFlush(const std::vector<Card>& setOfCards) const; 
};

#endif