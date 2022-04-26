#pragma once

#include <vector>
#include <memory>
#include "Verifier.hpp"

enum class Settlement {
    LOSE,
    WIN,
    DRAW };

class Comparator {
public:   
    Comparator(std::shared_ptr<Verifier> verifier) : verifier_(verifier) {};
    Settlement settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    PokerHand detectBestCombination(std::vector<Card>& setOfCards);

private:
    Settlement compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand);
    Settlement compareFullHouses(std::vector<Card> firstHand, std::vector<Card> secondHand);
    Settlement compareFourKinds(std::vector<Card> firstHand, std::vector<Card> secondHand);

    Card getLowestStraightCard(std::vector<Card>& setOfCards);
    Suit getSuitFromFlush(std::vector<Card>& setOfCards);
    std::vector<Card> getHighestTripleAndHighestPairCardFromFullHouse(std::vector<Card>& setOfCards);
    void sortCardsInHands(std::vector<Card>& firstHand, std::vector<Card>& secondHand);

    std::shared_ptr<Verifier> verifier_;
};
