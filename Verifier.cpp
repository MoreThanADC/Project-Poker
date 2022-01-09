#include "Verifier.hpp"

#include <algorithm>

PokerHand Verifier::verify(std::vector<Card>& setOfCards) {
    if (isRoyalFlush(setOfCards)) {
        return PokerHand::ROYALFLUSH;
    }  
    if (isStraightFlush(setOfCards)) {
        return PokerHand::STRAIGHTFLUSH;
    }  
    if (isFourKind(setOfCards)) {
        return PokerHand::FOURKIND;
    }
    if (isFullHouse(setOfCards)) {
        return PokerHand::FULLHUOSE;
    }
    if (isFlush(setOfCards)) {
        return PokerHand::FLUSH;
    }
    if (isStraight(setOfCards)) {
        return PokerHand::STRAIGHT;
    }
    if (isThreeKind(setOfCards)) {
        return PokerHand::THREEKIND;
    } 
    if (areTwoPairs(setOfCards)) {
        return PokerHand::TWOPAIRS;
    } 
    if (isAPair(setOfCards)) {
        return PokerHand::PAIR;
    } 
    return PokerHand::HIGHCARDS;
}

bool Verifier::isAPair(std::vector<Card>& setOfCards) {
    std::sort(begin(setOfCards), end(setOfCards));
    auto it = std::adjacent_find(begin(setOfCards), end(setOfCards));
    if (it != setOfCards.end()) {
        return true;
    }
    return false;
}

bool Verifier::areTwoPairs(std::vector<Card>& setOfCards) {
    int numberOfPairs = 0;
    std::sort(begin(setOfCards), end(setOfCards));

    auto it = std::adjacent_find(begin(setOfCards), end(setOfCards));
    if (it != setOfCards.end()) {
        numberOfPairs++;
    }

    auto it2 = std::adjacent_find(++it, end(setOfCards));
    if (it2 != setOfCards.end()) {
        numberOfPairs++;
    }

    return numberOfPairs  > 1 ? true : false;
}

bool Verifier::isThreeKind(std::vector<Card>& setOfCards) {
    std::sort(begin(setOfCards), end(setOfCards));
    for(const auto& el : setOfCards) {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 3, el);
        if (found != setOfCards.end()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isStraight(std::vector<Card>& setOfCards) {
    std::sort(begin(setOfCards), end(setOfCards));
    for (size_t i = 0 ; i < setOfCards.size() ; ++i) {
        if( setOfCards[i].getValue() + 1 == setOfCards[i+1].getValue() &&
            setOfCards[i].getValue() + 2 == setOfCards[i+2].getValue() && 
            setOfCards[i].getValue() + 3 == setOfCards[i+3].getValue() && 
            setOfCards[i].getValue() + 4 == setOfCards[i+4].getValue() ) {
            return true;
        } 
    }
    return false;
}

bool Verifier::isFlush(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isFullHouse(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isFourKind(std::vector<Card>& setOfCards) {
    std::sort(begin(setOfCards), end(setOfCards));
    for(const auto& el : setOfCards) {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 4, el);
        if (found != setOfCards.end()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isStraightFlush(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isRoyalFlush(const std::vector<Card>& setOfCards) {
    return true;
}