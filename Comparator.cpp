#include "Comparator.hpp"

Settlement Comparator::settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto pokerHand = verifier_->detectBestCombination(firstHand);

    sortCardsInHands(firstHand, secondHand);

    if (pokerHand == PokerHand::HIGHCARDS) {
        return compareHighestCard(firstHand, secondHand);
    }
    if (pokerHand == PokerHand::PAIR) {
        return comparePair(firstHand, secondHand);
    }
    if (pokerHand == PokerHand::TWOPAIRS) {
        return compareTwoPairs(firstHand, secondHand);
    }
    if (pokerHand == PokerHand::THREEKIND) {
        return compareThrees(firstHand, secondHand);
    }
    if (pokerHand == PokerHand::STRAIGHT) {
        return compareStraights(firstHand, secondHand);
    }
    // if (pokerHand == PokerHand::FLUSH) {
    //     return compareFlushes(firstHand, secondHand);
    // } 
    // if (pokerHand == PokerHand::FULLHOUSE) {
    //     return compareFullHouses(firstHand, secondHand);
    // } 
    // if (pokerHand == PokerHand::FOURKIND) {
    //     return compareFourKinds(firstHand, secondHand);
    // }
    // if (pokerHand == PokerHand::STRAIGHTFLUSH) {
    //     return compareStraights(firstHand, secondHand);
    // }

    return Settlement::DRAW;
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

    if ((*firstCard).getValue() > (*secondCard).getValue()) {
        return Settlement::WIN;
    } else if ((*firstCard).getValue() < (*secondCard).getValue()) {
        return Settlement::LOSE;
    } else {
        return compareHighestCard(firstHand, secondHand);
    }
}

Settlement Comparator::compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCard = std::adjacent_find(rbegin(firstHand), rend(firstHand));
    auto secondCard = std::adjacent_find(rbegin(secondHand), rend(secondHand));

    if ((*firstCard).getValue() > (*secondCard).getValue()) {
        return Settlement::WIN;
    } else if ((*firstCard).getValue() < (*secondCard).getValue()) {
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

    if ((firstCard).getValue() > (secondCard).getValue()) {
        return Settlement::WIN;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
        return Settlement::LOSE;
    } else {
        return compareHighestCard(firstHand, secondHand);
    }
}

Settlement Comparator::compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard = getLowestStraightCard(firstHand);
    Card secondCard = getLowestStraightCard(secondHand);

    if (firstCard.getValue() > secondCard.getValue()) {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is bigger than " << (secondCard).getValue() << '\n';
        return Settlement::WIN;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is less than " << (secondCard).getValue() << '\n';
        return Settlement::LOSE;
    } else {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is equal " << (secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

Card Comparator::getLowestStraightCard(std::vector<Card>& setOfCards) {
    std::cout << "liczba kart: " << setOfCards.size() << "\n";
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue()) {
            std::cout << "getLowestStraightCard: " << setOfCards[i].getValue() << "\n";
            return setOfCards[i];
        }
    }
    std::cout << "TU NIE MA STRAIGHTA!!!\n";
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
        if (firstHandWithSameSuits[i].getValue() > secondHandWithSameSuits[i].getValue()) {
            std::cout << "\nCompare card from flushes: " << firstHandWithSameSuits[i].getValue() << " is bigger than " << secondHandWithSameSuits[i].getValue() << '\n';
            return Settlement::WIN;
        }
        if (firstHandWithSameSuits[i].getValue() < secondHandWithSameSuits[i].getValue()) {
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

    if (firstPair[0].getValue() > secondPair[0].getValue()) {
        return Settlement::WIN;
    } 
    if (firstPair[0].getValue() < secondPair[0].getValue()) {
        return Settlement::LOSE;
    }
    if (firstPair[1].getValue()  > secondPair[1].getValue())  {
        return Settlement::WIN;
    } 
    if (firstPair[1].getValue()  < secondPair[1].getValue()) {
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
                                 return card.getValue() == (*foundTripleCard).getValue();
                             }),
                             setOfCards.end());

            auto foundPairCard = std::adjacent_find(begin(setOfCards), end(setOfCards));
            if (foundPairCard != setOfCards.end()) {
                cardsFromFull.push_back(*foundPairCard);
                setOfCards.erase(std::remove_if(setOfCards.begin(), setOfCards.end(), [&foundPairCard](const auto& card) {
                                 return card.getValue() == (*foundPairCard).getValue();
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

    if ((firstCard).getValue() > (secondCard).getValue()) {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is bigger than four kind " << (secondCard).getValue() << '\n';
        return Settlement::WIN;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
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