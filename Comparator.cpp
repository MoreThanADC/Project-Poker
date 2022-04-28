#include "Comparator.hpp"

Settlement Comparator::settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand)
{
    auto pokerHand = verifier_->detectBestCombination(firstHand);
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
        return compareFullHouses(firstHand, secondHand);
    case PokerHand::FOURKIND :
        return compareFourKinds(firstHand, secondHand);
    case PokerHand::STRAIGHTFLUSH :
        return compareStraights(firstHand, secondHand);
    default : return Settlement::DRAW;
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

Settlement Comparator::compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard;
    for (const auto& card : firstHand) {
        firstCard = *std::search_n(begin(firstHand), end(firstHand), 3, card);
    }
    Card secondCard;
    for (const auto& card : secondHand) {
        secondCard = *std::search_n(begin(secondHand), end(secondHand), 3, card);
    }

    if (firstCard > secondCard) {
        return Settlement::WIN;
    } else if (firstCard < secondCard) {
        return Settlement::LOSE;
    } else {
        return compareHighestCard(firstHand, secondHand);
    }
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
            std::cout << "\nCompare card from flushes: " << firstHandWithSameSuits[i].getValue() << " is bigger than " << secondHandWithSameSuits[i].getValue() << '\n';
            return Settlement::WIN;
        }
        if (firstHandWithSameSuits[i] < secondHandWithSameSuits[i]) {
            std::cout << "\nCompare card from flushes: " << firstHandWithSameSuits[i].getValue() << " is less than " << secondHandWithSameSuits[i].getValue() << '\n';
            return Settlement::LOSE;
        }
    }

    std::cout << "\nCompared cards from flushes are equal\n";
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

Settlement Comparator::compareFullHouses(std::vector<Card> firstHand, std::vector<Card> secondHand) {
    std::vector<Card> firstPair = getHighestTripleAndHighestPairCardFromFullHouse(firstHand);
    std::vector<Card> secondPair = getHighestTripleAndHighestPairCardFromFullHouse(secondHand);

    if (firstPair[0] > secondPair[0]) {
        return Settlement::WIN;
    } 
    if (firstPair[0] < secondPair[0]) {
        return Settlement::LOSE;
    }
    if (firstPair[1] > secondPair[1])  {
        return Settlement::WIN;
    } 
    if (firstPair[1] < secondPair[1]) {
        return Settlement::LOSE;
    } 

    return compareHighestCard(firstHand, secondHand);
}

std::vector<Card> Comparator::getHighestTripleAndHighestPairCardFromFullHouse(std::vector<Card>& setOfCards) {
    std::vector<Card> cardsFromFull;
    for (const auto& el : setOfCards) {
        auto foundTripleCard = std::search_n(rbegin(setOfCards), rend(setOfCards), 3, el);
        if (foundTripleCard != setOfCards.rend()) {
            cardsFromFull.push_back(*foundTripleCard);
            setOfCards.erase(std::remove_if(setOfCards.begin(), setOfCards.end(), [&foundTripleCard](const auto& card) {
                                return card == *foundTripleCard;
                             }),
                             setOfCards.end());

            auto foundPairCard = std::adjacent_find(begin(setOfCards), end(setOfCards));
            if (foundPairCard != setOfCards.end()) {
                cardsFromFull.push_back(*foundPairCard);
                setOfCards.erase(std::remove_if(setOfCards.begin(), setOfCards.end(), [&foundPairCard](const auto& card) {
                                 return card == *foundPairCard;
                            }),
                            setOfCards.end());
            }
        }
    }

    return cardsFromFull;
}

Settlement Comparator::compareFourKinds(std::vector<Card> firstHand, std::vector<Card> secondHand) {
    Card firstCard;
    for (const auto& card : firstHand) {
        firstCard = *std::search_n(begin(firstHand), end(firstHand), 4, card);
    }
    Card secondCard;
    for (const auto& card : secondHand) {
        secondCard = *std::search_n(begin(secondHand), end(secondHand), 4, card);
    }

    if (firstCard > secondCard) {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is bigger than four kind " << (secondCard).getValue() << '\n';
        return Settlement::WIN;
    } else if (firstCard < secondCard) {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is less than four kind " << (secondCard).getValue() << '\n';
        return Settlement::LOSE;
    } else {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is equal " << (secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

PokerHand Comparator::detectBestCombination(std::vector<Card>& setOfCards) {
    return verifier_->detectBestCombination(setOfCards);
}

void Comparator::sortCardsInHands(std::vector<Card>& firstHand, std::vector<Card>& secondHand)
{
    std::sort(firstHand.begin(), firstHand.end());
    std::sort(secondHand.begin(), secondHand.end());
}