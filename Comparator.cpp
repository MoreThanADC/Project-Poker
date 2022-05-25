#include "Comparator.hpp"
#include "Helpers.hpp"

#include <algorithm>

Settlement Comparator::calculateBetterHand(std::vector<Card> firstHand, std::vector<Card> secondHand) const
{
    auto firstCombination = verifier_->detectBestCombination(firstHand);
    auto secondCombination = verifier_->detectBestCombination(secondHand);

    if (firstCombination > secondCombination)
    {
        return Settlement::WIN;
    } 
    if (firstCombination < secondCombination)
    {
        return Settlement::LOSE;
    }

    return settleTheTie(firstHand, secondHand, firstCombination);
}

Settlement Comparator::settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand, const PokerHand& pokerHand) const
{
    sortCardsInHands(firstHand, secondHand);
    
    switch (pokerHand)
    {
    case PokerHand::HIGHCARDS :
        return compareHighestCard(firstHand, secondHand);
    case PokerHand::PAIR :
        return comparePair(firstHand, secondHand);
    case PokerHand::TWOPAIRS :
        return compareTwoPairs(firstHand, secondHand);
    case PokerHand::THREEKIND :
        return compareThrees(firstHand, secondHand);
    case PokerHand::STRAIGHT :
        return compareStraights(firstHand, secondHand);
    case PokerHand::FLUSH :
        return compareFlushes(firstHand, secondHand);
    case PokerHand::FULLHOUSE :
        return compareThrees(firstHand, secondHand); // We can use threes comparator, because in deck (52 cards) may be just only one unique three and it enough
    case PokerHand::FOURKIND :
        return compareThrees(firstHand, secondHand); // We can use threes comparator, because in deck (52 cards) may be just only one unique three and it enough
    case PokerHand::STRAIGHTFLUSH :
        return compareStraights(firstHand, secondHand); // we can use straights comparator, because kind of suit doesn't matter
    default :
        return Settlement::DRAW;
    }
}

Settlement Comparator::compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    for (size_t i = firstHand.size(); i > 0; i--)
    {
        if (firstHand[i].getValue() > secondHand[i].getValue()) 
        {
            return Settlement::WIN;
        } 
        if (firstHand[i].getValue() < secondHand[i].getValue())
        {
            return Settlement::LOSE;
        }
    }

    return Settlement::DRAW;
}

Settlement Comparator::comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    auto firstCard = std::ranges::adjacent_find(firstHand);
    auto secondCard = std::ranges::adjacent_find(secondHand);

    if (*firstCard > *secondCard)
    {
        return Settlement::WIN;
    } 
    if (*firstCard < *secondCard)
    {
        return Settlement::LOSE;
    }

    return compareHighestCard(firstHand, secondHand);
}

Settlement Comparator::compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    auto firstCard = std::adjacent_find(rbegin(firstHand), rend(firstHand));
    auto secondCard = std::adjacent_find(rbegin(secondHand), rend(secondHand));

    if (*firstCard > *secondCard)
    {
        return Settlement::WIN;
    } 
    if (*firstCard < *secondCard) 
    {
        return Settlement::LOSE;
    } 
        
    return comparePair(firstHand, secondHand);
}

Card Comparator::getCardFromThree(const std::vector<Card>& hand) const
{
    for (const auto& card : hand)
    {
        auto foundCards = std::ranges::search_n(hand, 3, card);
        if (!foundCards.empty()) 
        {
            return foundCards.front();
        }
    }
    return hand.front();
}

Settlement Comparator::compareThrees(const std::vector<Card>& firstHand, const std::vector<Card>& secondHand) const
{
    Card firstCard = getCardFromThree(firstHand);
    Card secondCard = getCardFromThree(secondHand);

    return firstCard > secondCard ? Settlement::WIN : Settlement::LOSE;
}

Settlement Comparator::compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    Card firstCard = getLowestStraightCard(firstHand);
    Card secondCard = getLowestStraightCard(secondHand);

    if (firstCard > secondCard) 
    {
        return Settlement::WIN;
    } 
    if (firstCard < secondCard) 
    {
        return Settlement::LOSE;
    }

    return compareHighestCard(firstHand, secondHand);
}

Card Comparator::getLowestStraightCard(std::vector<Card>& setOfCards) const
{
    std::vector<Card> cardsWithoutDuplicatedRanks;
    std::ranges::unique_copy(setOfCards, std::back_inserter(cardsWithoutDuplicatedRanks), [](const auto& first, const auto& second){
            return first == second;
        });

    for (size_t i = 0; i < cardsWithoutDuplicatedRanks.size(); ++i) 
    {
        if (cardsWithoutDuplicatedRanks[i].getValue() + 1 == cardsWithoutDuplicatedRanks[i + 1].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 2 == cardsWithoutDuplicatedRanks[i + 2].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 3 == cardsWithoutDuplicatedRanks[i + 3].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 4 == cardsWithoutDuplicatedRanks[i + 4].getValue()) 
        {
            return cardsWithoutDuplicatedRanks[i];
        }
    }
    // Ace value equal 14 for hight straight
    for (auto& card : cardsWithoutDuplicatedRanks)
    {
        if (card.getRank() == Rank::ACE)
        {
            card.setValue(1);
        }
    }
    std::ranges::sort(cardsWithoutDuplicatedRanks, helpers::sortDescending);

    for (size_t i = 0; i < cardsWithoutDuplicatedRanks.size(); ++i) {
        if (cardsWithoutDuplicatedRanks[i].getValue() + 1 == cardsWithoutDuplicatedRanks[i + 1].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 2 == cardsWithoutDuplicatedRanks[i + 2].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 3 == cardsWithoutDuplicatedRanks[i + 3].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 4 == cardsWithoutDuplicatedRanks[i + 4].getValue())
        {
            return cardsWithoutDuplicatedRanks[i];
        }
    }

    return setOfCards.front();
}

Settlement Comparator::compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    std::vector<Card> firstHandWithSameSuits;
    std::vector<Card> secondHandWithSameSuits;

    for (size_t i = 0; i < firstHand.size(); ++i)
    {
        if (firstHand[i].getSuit() == getSuitFromFlush(firstHand)) 
        {
            firstHandWithSameSuits.push_back(firstHand[i]);
        }
        if (secondHand[i].getSuit() == getSuitFromFlush(secondHand)) 
        {
            secondHandWithSameSuits.push_back(secondHand[i]);
        }
    }

    std::ranges::reverse(firstHandWithSameSuits);
    std::ranges::reverse(secondHandWithSameSuits);

    size_t lengthOfShorterVector = firstHandWithSameSuits.size() >= secondHandWithSameSuits.size() ?
        secondHandWithSameSuits.size() : firstHandWithSameSuits.size();

    for (size_t i = 0; i < lengthOfShorterVector; ++i)
    {
        if (firstHandWithSameSuits[i] > secondHandWithSameSuits[i])
        {
            return Settlement::WIN;
        }
        if (firstHandWithSameSuits[i] < secondHandWithSameSuits[i])
        {
            return Settlement::LOSE;
        }
    }

    return compareHighestCard(firstHand, secondHand);
}

Suit Comparator::getSuitFromFlush(const std::vector<Card>& setOfCards) const
{
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getSuit() == setOfCards[i+1].getSuit() && setOfCards[i].getSuit() == setOfCards[i+2].getSuit()) {
            return setOfCards[i].getSuit();
        }
        if (setOfCards[i].getSuit() == setOfCards[i+2].getSuit() && setOfCards[i].getSuit() == setOfCards[i+3].getSuit()) {
            return setOfCards[i].getSuit();
        }
        if (setOfCards[i].getSuit() == setOfCards[i+3].getSuit() && setOfCards[i].getSuit() == setOfCards[i+4].getSuit()) {
            return setOfCards[i].getSuit();
        }
    }

    return Suit::SPADES;
}

void Comparator::sortCardsInHands(std::vector<Card>& firstHand, std::vector<Card>& secondHand) const
{
    std::ranges::sort(firstHand, helpers::sortDescending);
    std::ranges::sort(secondHand, helpers::sortDescending);
}