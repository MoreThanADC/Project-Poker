#include "Comparator.hpp"

bool Comparator::settleTheTie(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto pokerHand = verifier_->detectBestCombination(firstHand);
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
    if (pokerHand == PokerHand::FLUSH) {
        return compareFlushes(firstHand, secondHand);
    } 
    if (pokerHand == PokerHand::FULLHOUSE) {
        return compareFullHouses(firstHand, secondHand);
    } 
    if (pokerHand == PokerHand::FOURKIND) {
        return compareFourKinds(firstHand, secondHand);
    }
    if (pokerHand == PokerHand::STRAIGHTFLUSH) {
        return compareStraights(firstHand, secondHand);
    }

    return false;
}

bool Comparator::compareHighestCard(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    for (size_t i = firstHand.size(); i > 0; i--) {
        if (firstHand[i].getValue() > secondHand[i].getValue()) {
            std::cout << "\nCompare Highest number: " << firstHand[i].getValue() << " is biggeer than " << secondHand[i].getValue() << '\n';
            return true;
        } else if (firstHand[i].getValue() < secondHand[i].getValue()) {
            std::cout << "\nCompare Highest number: " << firstHand[i].getValue() << " is less than " << secondHand[i].getValue() << '\n';
            return false;
        }
    }
    std::cout << "\nDRAW!!!\n";
    return false;
}

bool Comparator::comparePair(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCard = std::adjacent_find(begin(firstHand), end(firstHand));
    auto secondCard = std::adjacent_find(begin(secondHand), end(secondHand));

    if ((*firstCard).getValue() > (*secondCard).getValue()) {
        std::cout << "\nCompare a pair: " << (*firstCard).getValue() << " is bigger than " << (*secondCard).getValue() << '\n';
        return true;
    } else if ((*firstCard).getValue() < (*secondCard).getValue()) {
        std::cout << "\nCompare a pair: " << (*firstCard).getValue() << " is less than " << (*secondCard).getValue() << '\n';
        return false;
    } else {
        std::cout << "\nCompare a pair: " << (*firstCard).getValue() << " is equal " << (*secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

bool Comparator::compareTwoPairs(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCard = std::adjacent_find(rbegin(firstHand), rend(firstHand));
    auto secondCard = std::adjacent_find(rbegin(secondHand), rend(secondHand));

    if ((*firstCard).getValue() > (*secondCard).getValue()) {
        std::cout << "\nCompare first (the biggest) pair: " << (*firstCard).getValue() << " is bigger than " << (*secondCard).getValue() << '\n';
        return true;
    } else if ((*firstCard).getValue() < (*secondCard).getValue()) {
        std::cout << "\nCompare first (the biggest) pair: " << (*firstCard).getValue() << " is less than " << (*secondCard).getValue() << '\n';
        return false;
    } else {
        std::cout << "\nCompare first (the biggest) pair: " << (*firstCard).getValue() << " is equal " << (*secondCard).getValue() << '\n';
        return comparePair(firstHand, secondHand);
    }
}

bool Comparator::compareThrees(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard;
    for (const auto& card : firstHand) {
        firstCard = *std::search_n(begin(firstHand), end(firstHand), 3, card);
    }
    Card secondCard;
    for (const auto& card : secondHand) {
        secondCard = *std::search_n(begin(secondHand), end(secondHand), 3, card);
    }

    if ((firstCard).getValue() > (secondCard).getValue()) {
        std::cout << "\nCompare card from three: " << (firstCard).getValue() << " is bigger than " << (secondCard).getValue() << '\n';
        return true;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
        std::cout << "\nCompare card from three: " << (firstCard).getValue() << " is less than " << (secondCard).getValue() << '\n';
        return false;
    } else {
        std::cout << "\nCompare card from three: " << (firstCard).getValue() << " is equal " << (secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

bool Comparator::compareStraights(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    Card firstCard = getLowestStraightCard(firstHand);
    Card secondCard = getLowestStraightCard(secondHand);

    if (firstCard.getValue() > secondCard.getValue()) {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is bigger than " << (secondCard).getValue() << '\n';
        return true;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is less than " << (secondCard).getValue() << '\n';
        return false;
    } else {
        std::cout << "\nCompare lowest card from straight: " << (firstCard).getValue() << " is equal " << (secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

Card Comparator::getLowestStraightCard(std::vector<Card>& setOfCards) {
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue()) {
            return setOfCards[i];
        }
    }
    return setOfCards[0];
}

bool Comparator::compareFlushes(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
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
            return true;
        }
        if (firstHandWithSameSuits[i].getValue() < secondHandWithSameSuits[i].getValue()) {
            std::cout << "\nCompare card from flushes: " << firstHandWithSameSuits[i].getValue() << " is less than " << secondHandWithSameSuits[i].getValue() << '\n';
            return false;
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


bool Comparator::compareFullHouses(std::vector<Card> firstHand, std::vector<Card> secondHand) {
    std::vector<Card> firstPair = getHighestTripleAndHighestPairCardFromFullHouse(firstHand);
    std::vector<Card> secondPair = getHighestTripleAndHighestPairCardFromFullHouse(secondHand);

    if (firstPair[0].getValue() > secondPair[0].getValue()) {
        return true;
    } 
    if (firstPair[0].getValue() < secondPair[0].getValue()) {
        return false;
    }
    if (firstPair[1].getValue()  > secondPair[1].getValue())  {
        return true;
    } 
    if (firstPair[1].getValue()  < secondPair[1].getValue()) {
        return false;
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

bool Comparator::compareFourKinds(std::vector<Card> firstHand, std::vector<Card> secondHand) {
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
        return true;
    } else if ((firstCard).getValue() < (secondCard).getValue()) {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is less than four kind " << (secondCard).getValue() << '\n';
        return false;
    } else {
        std::cout << "\nCompare card from four kind: " << (firstCard).getValue() << " is equal " << (secondCard).getValue() << '\n';
        return compareHighestCard(firstHand, secondHand);
    }
}

PokerHand Comparator::detectBestCombination(std::vector<Card>& setOfCards) {
    return verifier_->detectBestCombination(setOfCards);
}