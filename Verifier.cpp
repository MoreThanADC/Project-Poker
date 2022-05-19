#include "Verifier.hpp"

#include <algorithm>
#include <map>

namespace
{

std::map<Suit, int> countSuits(const std::vector<Card>& setOfCards)
{
    std::map<Suit, int> numberOfCardsInSameSuit = { {Suit::SPADES, 0},
                                                    {Suit::HEARTS, 0},
                                                    {Suit::DIAMONDS, 0},
                                                    {Suit::CLUBS, 0} };
    for (const auto& card : setOfCards) 
    {
        numberOfCardsInSameSuit[card.getSuit()]++;
    }

    return numberOfCardsInSameSuit;
}

Suit getDominantSuit(const std::vector<Card>& setOfCards) 
{
    std::map<Suit, int> numberOfCardsInSameSuit = countSuits(setOfCards);

    for (const auto& [key, value] : numberOfCardsInSameSuit)
    {
        if (value >= 5)
            return key;
    }

    return Suit::SPADES;
}

} // namespace 

PokerHand Verifier::detectBestCombination(std::vector<Card> setOfCards)
{
    std::sort(begin(setOfCards), end(setOfCards));

    if (isRoyalFlush(setOfCards)) 
        return PokerHand::ROYALFLUSH;
    if (isStraightFlush(setOfCards))
        return PokerHand::STRAIGHTFLUSH;
    if (isFourKind(setOfCards))
        return PokerHand::FOURKIND;
    if (isFullHouse(setOfCards))
        return PokerHand::FULLHOUSE;
    if (isFlush(setOfCards))
        return PokerHand::FLUSH;
    if (isStraight(setOfCards))
        return PokerHand::STRAIGHT;
    if (isThreeKind(setOfCards))
        return PokerHand::THREEKIND;
    if (areTwoPairs(setOfCards))
        return PokerHand::TWOPAIRS;
    if (isAPair(setOfCards))
        return PokerHand::PAIR;

    return PokerHand::HIGHCARDS;
}

bool Verifier::isAPair(const std::vector<Card>& setOfCards) const
{
    auto it = std::adjacent_find(begin(setOfCards), end(setOfCards));
    return it != setOfCards.end();
}

bool Verifier::areTwoPairs(const std::vector<Card>& setOfCards) const
{
    auto it = std::adjacent_find(begin(setOfCards), end(setOfCards));
    if (it == setOfCards.end()) {
        return false;
    }

    auto it2 = std::adjacent_find(++it, end(setOfCards));
    if (it2 == setOfCards.end()) {
        return false;
    }

    return true;
}

bool Verifier::isThreeKind(const std::vector<Card>& setOfCards) const
{
    for (const auto& card : setOfCards) {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 3, card);
        if (found != setOfCards.end()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isStraight(const std::vector<Card>& setOfCards) const
{
    std::vector<Card> uniqueCards {};

    std::unique_copy(
        begin(setOfCards),
        end(setOfCards),
        std::back_inserter(uniqueCards),
        [](const auto& first, const auto& second) {
            return first == second;
        });

    // Ace value equal 14 for hight straight
    for (size_t i = 0; i < uniqueCards.size(); ++i) {
        if (uniqueCards[i].getValue() + 1 == uniqueCards[i + 1].getValue() &&
            uniqueCards[i].getValue() + 2 == uniqueCards[i + 2].getValue() &&
            uniqueCards[i].getValue() + 3 == uniqueCards[i + 3].getValue() &&
            uniqueCards[i].getValue() + 4 == uniqueCards[i + 4].getValue()) {
            return true;
        }
    }

    // Ace value equal 1 for low straight
    for (auto& card : uniqueCards) {
        if (card.getRank() == Rank::ACE) {
            card.setValue(1);
        }
    }
    std::sort(begin(uniqueCards), end(uniqueCards));

    for (size_t i = 0; i < uniqueCards.size(); ++i) {
        if (uniqueCards[i].getValue() + 1 == uniqueCards[i + 1].getValue() &&
            uniqueCards[i].getValue() + 2 == uniqueCards[i + 2].getValue() &&
            uniqueCards[i].getValue() + 3 == uniqueCards[i + 3].getValue() &&
            uniqueCards[i].getValue() + 4 == uniqueCards[i + 4].getValue()) {
            return true;
        }
    }

    return false;
}

bool Verifier::isFlush(const std::vector<Card>& setOfCards) const
{
    std::map<Suit, int> numberOfCardsInSameSuit = countSuits(setOfCards);

    for (const auto& [key, value] : numberOfCardsInSameSuit)
    {
        if (value >= 5)
            return true;
    }

    return false;
}

bool Verifier::isFullHouse(const std::vector<Card>& setOfCards) const
{
    for (const auto& el : setOfCards) 
    {
        auto found = std::search_n(rbegin(setOfCards), rend(setOfCards), 3, el);
        if (found != setOfCards.rend()) 
        {
            std::vector<Card> cardsWithoutTriple = {};
            cardsWithoutTriple.reserve(4);
            
            std::copy_if(setOfCards.begin(), setOfCards.end(), std::back_inserter(cardsWithoutTriple), [&found](const auto& card){
                return card.getValue() != (*found).getValue();
            });

            return isAPair(cardsWithoutTriple); 
        }
    }
    return false;
}

bool Verifier::isFourKind(const std::vector<Card>& setOfCards) const
{
    for (const auto& card : setOfCards) 
    {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 4, card);

        if (found != setOfCards.end()) 
            return true;
    }

    return false;
}

bool Verifier::isStraightFlush(const std::vector<Card>& setOfCards) const 
{
    std::vector<Card> uniqueCards;
    std::unique_copy(
        begin(setOfCards),
        end(setOfCards),
        std::back_inserter(uniqueCards),
        [](const auto& first, const auto& second) {
            return first == second;
        });
    
    // Ace value equal 14 for hight straight
    for (size_t i = 0; i < uniqueCards.size(); ++i) 
    {
        if (uniqueCards[i].getValue() + 1 == uniqueCards[i + 1].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 1].getSuit() &&
            uniqueCards[i].getValue() + 2 == uniqueCards[i + 2].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 2].getSuit() &&
            uniqueCards[i].getValue() + 3 == uniqueCards[i + 3].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 3].getSuit() &&
            uniqueCards[i].getValue() + 4 == uniqueCards[i + 4].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 4].getSuit())
        {
            return true;
        }
    }
    // Ace value equal 1 for low straight
    for (auto& card : uniqueCards)
    {
        if (card.getRank() == Rank::ACE)
            card.setValue(1);
    }
    std::sort(begin(uniqueCards), end(uniqueCards));

    for (size_t i = 0; i < uniqueCards.size(); ++i) {
        if (uniqueCards[i].getValue() + 1 == uniqueCards[i + 1].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 1].getSuit() &&
            uniqueCards[i].getValue() + 2 == uniqueCards[i + 2].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 2].getSuit() &&
            uniqueCards[i].getValue() + 3 == uniqueCards[i + 3].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 3].getSuit() &&
            uniqueCards[i].getValue() + 4 == uniqueCards[i + 4].getValue() &&
            uniqueCards[i].getSuit() == uniqueCards[i + 4].getSuit()) 
        {
            return true;
        }
    }
    return false;
}

bool Verifier::isRoyalFlush(const std::vector<Card>& setOfCards) const 
{
    Suit dominantSuit = getDominantSuit(setOfCards);
    std::vector<Card> uniqueCards {};

    std::unique_copy(
        begin(setOfCards),
        end(setOfCards),
        std::back_inserter(uniqueCards),
        [&dominantSuit](const auto& first, const auto& second) {
            if (first == second && first.getSuit() == dominantSuit) {
                return true;
            }
            return false;
        });

    for (size_t i = 0; i < uniqueCards.size(); ++i) {
        if (setOfCards[i].getRank() == Rank::TEN) {
            if (uniqueCards[i].getValue() + 1 == uniqueCards[i + 1].getValue() &&
                uniqueCards[i].getSuit() == uniqueCards[i + 1].getSuit() &&
                uniqueCards[i].getValue() + 2 == uniqueCards[i + 2].getValue() &&
                uniqueCards[i].getSuit() == uniqueCards[i + 2].getSuit() &&
                uniqueCards[i].getValue() + 3 == uniqueCards[i + 3].getValue() &&
                uniqueCards[i].getSuit() == uniqueCards[i + 3].getSuit() &&
                uniqueCards[i].getValue() + 4 == uniqueCards[i + 4].getValue() &&
                uniqueCards[i].getSuit() == uniqueCards[i + 4].getSuit()) {
                return true;
            }
        }
    }
    return false;
}

std::string Verifier::printPokerHand(const PokerHand& pokerHand) const
{
    switch (pokerHand) {
    case PokerHand::ROYALFLUSH:
        return "Royal flush";
    case PokerHand::STRAIGHTFLUSH:
        return "Straight flush";
    case PokerHand::FOURKIND:
        return "Four of a kind";
    case PokerHand::FULLHOUSE:
        return "Full house";
    case PokerHand::FLUSH:
        return "Flush";
    case PokerHand::STRAIGHT:
        return "Straight";
    case PokerHand::THREEKIND:
        return "Three of a kind";
    case PokerHand::TWOPAIRS:
        return "Two pair";
    case PokerHand::PAIR:
        return "Pair";
    case PokerHand::HIGHCARDS:
    default:
        return "High Card";
    }
}
