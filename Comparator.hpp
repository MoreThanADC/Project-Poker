#ifndef COMPARATOR_HPP
#define COMPARATOR_HPP

#include <vector>
#include <memory>

#include "Verifier.hpp"

enum class Settlement {
    LOSE,
    WIN,
    DRAW };

class Comparator {
public:   
    explicit Comparator(std::shared_ptr<Verifier> verifier) : verifier_(verifier) {};
    Settlement calculateBetterHand(std::vector<Card> firstHand, std::vector<Card> secondHand) const;

private:
    Settlement settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand, const PokerHand& pokerHand) const;

    Settlement compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;
    Settlement comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;
    Settlement compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;
    Settlement compareThrees(const std::vector<Card>& firstHand, const std::vector<Card>& secondHand) const;
    Settlement compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;
    Settlement compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;

    Card getLowestStraightCard(std::vector<Card>& setOfCards) const;
    Suit getSuitFromFlush(const std::vector<Card>& setOfCards) const;
    Card getCardFromThree(const std::vector<Card>& hand) const;

    void sortCardsInHands(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const;

    std::shared_ptr<Verifier> verifier_;
};

#endif