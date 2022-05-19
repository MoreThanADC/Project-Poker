#include "Comparator.hpp"

Settlement Comparator::calculateBetterHand(std::vector<Card> firstHand, std::vector<Card> secondHand) {
    auto firstCombination = verifier_->detectBestCombination(firstHand);
    auto secondCombination = verifier_->detectBestCombination(secondHand);

    if (firstCombination > secondCombination) {
        return Settlement::WIN;
    } else if (firstCombination < secondCombination) {
        return Settlement::LOSE;
    } else {
        return settleTheTie(firstHand, secondHand, firstCombination);
    }
}

Settlement Comparator::settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand, const PokerHand& pokerHand)
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
        return compareStraights(firstHand, secondHand); // we can use straights comparator, because kidn of suit doesn't matter
    default :
        return Settlement::DRAW;
    }
}

Settlement Comparator::compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    for (size_t i = firstHand.size(); i > 0; i--) {
        if (firstHand[i].getValue() > secondHand[i].getValue()) {
            return Settlement::WIN;
        } else if (firstHand[i].getValue() < secondHand[i].getValue()) {
            return Settlement::LOSE;
        }
    }

    return Settlement::DRAW;
}

Settlement Comparator::comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCard = std::adjacent_find(begin(firstHand), end(firstHand));
    auto secondCard = std::adjacent_find(begin(secondHand), end(secondHand));

    if (*firstCard > *secondCard) {
        return Settlement::WIN;
    } else if (*firstCard < *secondCard) {
        return Settlement::LOSE;
    } else {
        return compareHighestCard(firstHand, secondHand);
    }
}

Settlement Comparator::compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCard = std::adjacent_find(rbegin(firstHand), rend(firstHand));
    auto secondCard = std::adjacent_find(rbegin(secondHand), rend(secondHand));

    if (*firstCard > *secondCard) {
        return Settlement::WIN;
    } else if (*firstCard < *secondCard) {
        return Settlement::LOSE;
    } else {
        return comparePair(firstHand, secondHand);
    }
}

Card Comparator::getCardFromThree(std::vector<Card>& hand) {
    std::sort(begin(hand), end(hand), [](auto& first, auto second){
        return first > second;
    });

    for (const auto& card : hand) {
        auto it = std::search_n(begin(hand), end(hand), 3, card);
        if (it != hand.end()) {
            return *it;
        }
    }
    return hand[0];
}

Settlement Comparator::compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard = getCardFromThree(firstHand);
    Card secondCard = getCardFromThree(secondHand);

    return firstCard > secondCard ? Settlement::WIN : Settlement::LOSE;
}

Settlement Comparator::compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard = getLowestStraightCard(firstHand);
    Card secondCard = getLowestStraightCard(secondHand);

    if (firstCard > secondCard) {
        return Settlement::WIN;
    } else if (firstCard < secondCard) {
        return Settlement::LOSE;
    } else {
        return compareHighestCard(firstHand, secondHand);
    }
}

Card Comparator::getLowestStraightCard(std::vector<Card>& setOfCards) {
    std::vector<Card> cardsWithoutDuplicatedRanks;
    std::unique_copy(
        begin(setOfCards), 
        end(setOfCards), 
        std::back_inserter(cardsWithoutDuplicatedRanks), 
        [](const auto& first, const auto& second) {
            return first == second;
        });

    for (size_t i = 0; i < cardsWithoutDuplicatedRanks.size(); ++i) {
        if (cardsWithoutDuplicatedRanks[i].getValue() + 1 == cardsWithoutDuplicatedRanks[i + 1].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 2 == cardsWithoutDuplicatedRanks[i + 2].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 3 == cardsWithoutDuplicatedRanks[i + 3].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 4 == cardsWithoutDuplicatedRanks[i + 4].getValue()) {
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
    std::sort(begin(cardsWithoutDuplicatedRanks), end(cardsWithoutDuplicatedRanks));

    for (size_t i = 0; i < cardsWithoutDuplicatedRanks.size(); ++i) {
        if (cardsWithoutDuplicatedRanks[i].getValue() + 1 == cardsWithoutDuplicatedRanks[i + 1].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 2 == cardsWithoutDuplicatedRanks[i + 2].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 3 == cardsWithoutDuplicatedRanks[i + 3].getValue() &&
            cardsWithoutDuplicatedRanks[i].getValue() + 4 == cardsWithoutDuplicatedRanks[i + 4].getValue()) {
            return cardsWithoutDuplicatedRanks[i];
        }
    }

    return setOfCards[0];
}

Settlement Comparator::compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Suit firstCardSuit = getSuitFromFlush(firstHand);
    Suit secondCardSuit = getSuitFromFlush(secondHand);

    std::vector<Card> firstHandWithSameSuits;
    std::vector<Card> secondHandWithSameSuits;

    for (size_t i = 0; i < firstHand.size(); ++i) {
        if (firstHand[i].getSuit() == firstCardSuit) {
            firstHandWithSameSuits.push_back(firstHand[i]);
        }
        if (secondHand[i].getSuit() == secondCardSuit) {
            secondHandWithSameSuits.push_back(secondHand[i]);
        }
    }

    std::reverse(begin(firstHandWithSameSuits), end(firstHandWithSameSuits));
    std::reverse(begin(secondHandWithSameSuits), end(secondHandWithSameSuits));
   
    size_t lengthOfShorterVector;

    if (firstHandWithSameSuits.size() >= secondHandWithSameSuits.size()) {
        lengthOfShorterVector = secondHandWithSameSuits.size();
    } else {
        lengthOfShorterVector = firstHandWithSameSuits.size();
    }

    for (size_t i = 0; i < lengthOfShorterVector; ++i) {
        if (firstHandWithSameSuits[i] > secondHandWithSameSuits[i]) {
            return Settlement::WIN;
        }
        if (firstHandWithSameSuits[i] < secondHandWithSameSuits[i]) {
            return Settlement::LOSE;
        }
    }

    return compareHighestCard(firstHand, secondHand);
}

Suit Comparator::getSuitFromFlush(std::vector<Card>& setOfCards) {
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

void Comparator::sortCardsInHands(std::vector<Card>& firstHand, std::vector<Card>& secondHand)
{
    std::sort(firstHand.begin(), firstHand.end());
    std::sort(secondHand.begin(), secondHand.end());
}