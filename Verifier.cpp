#include "Verifier.hpp"

PokerHand Verifier::verify(const std::vector<Card>& setOfCards) {
    if (isPoker(setOfCards)) {
        return PokerHand::POKER;
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

bool Verifier::isAPair(const std::vector<Card>& setOfCards) {
    return true;
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

bool Verifier::isPoker(const std::vector<Card>& setOfCards) {
    return true;
}