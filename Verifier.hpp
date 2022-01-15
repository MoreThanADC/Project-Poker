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
                       FULLHUOSE,
                       FOURKIND,
                       STRAIGHTFLUSH,
                       ROYALFLUSH };

class Verifier {
public:
    PokerHand detectBestCombination(std::vector<Card>& setOfCards);
    bool isPlayerWinner(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    std::string printPokerHand(PokerHand pokerHand);

private:
    bool isAPair(std::vector<Card>& setOfCards);
    bool areTwoPairs(std::vector<Card>& setOfCards);
    bool isThreeKind(std::vector<Card>& setOfCards);
    bool isStraight(std::vector<Card> setOfCards);
    bool isFlush(const std::vector<Card>& setOfCards);
    bool isFullHouse(std::vector<Card> setOfCards);
    bool isFourKind(std::vector<Card>& setOfCards);
    bool isStraightFlush(std::vector<Card> setOfCards);
    bool isRoyalFlush(const std::vector<Card>& setOfCards);

    bool settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand, PokerHand& pokerHand);
    bool compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Card getLowestStraightCard(std::vector<Card>& setOfCards);
    bool compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Suit getSuitFromFlush(std::vector<Card>& setOfCards);
    bool compareFullHouses(std::vector<Card> firstHand, std::vector<Card> secondHand);
    std::vector<Card> getHighestTripleAndHighestPairCardFromFullHouse(std::vector<Card>& setOfCards);

};
