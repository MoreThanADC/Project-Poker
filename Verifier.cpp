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

bool Verifier::areTwoPairs(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isThreeKind(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isStraight(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isFlush(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isFullHouse(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isFourKind(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isStraightFlush(const std::vector<Card>& setOfCards) {
    return true;
}

bool Verifier::isRoyalFlush(const std::vector<Card>& setOfCards) {
    return true;
}