#pragma once

#include <vector>
#include <memory>
#include "Verifier.hpp"

class Comparator {
public:   
    Comparator(std::shared_ptr<Verifier> verifier) : verifier_(verifier) {};
    bool settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand);

    bool compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    bool compareFullHouses(std::vector<Card> firstHand, std::vector<Card> secondHand);
    bool compareFourKinds(std::vector<Card> firstHand, std::vector<Card> secondHand);

    PokerHand detectBestCombination(std::vector<Card>& setOfCards);

private:
    Card getLowestStraightCard(std::vector<Card>& setOfCards);
    Suit getSuitFromFlush(std::vector<Card>& setOfCards);
    std::vector<Card> getHighestTripleAndHighestPairCardFromFullHouse(std::vector<Card>& setOfCards);

    std::shared_ptr<Verifier> verifier_;
};
