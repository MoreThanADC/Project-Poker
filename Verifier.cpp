#include "Verifier.hpp"

#include <algorithm>

PokerHand Verifier::detectBestCombination(std::vector<Card>& setOfCards) {
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
        return PokerHand::FULLHOUSE;
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
    auto it = std::adjacent_find(rbegin(setOfCards), rend(setOfCards));
    if (it != setOfCards.rend()) {
        return true;
    }
    return false;
}

bool Verifier::areTwoPairs(std::vector<Card>& setOfCards) {
    int numberOfPairs = 0;

    auto it = std::adjacent_find(begin(setOfCards), end(setOfCards));
    if (it != setOfCards.end()) {
        numberOfPairs++;
    }

    auto it2 = std::adjacent_find(++it, end(setOfCards));
    if (it2 != setOfCards.end()) {
        numberOfPairs++;
    }

    return numberOfPairs > 1 ? true : false;
}

bool Verifier::isThreeKind(std::vector<Card>& setOfCards) {
    for (const auto& card : setOfCards) {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 3, card);
        if (found != setOfCards.end()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isStraight(std::vector<Card> setOfCards) {
    // Ace value equal 14 for hight straight
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue()) {
            return true;
        }
    }
    // Ace value equal 1 for low straight
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getRank() == Rank::ACE) {
            setOfCards[i].setValue(1);
        }
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isFlush(const std::vector<Card>& setOfCards) {
    int spades = 0;
    int hearts = 0;
    int diamonds = 0;
    int clubs = 0;

    for (const auto& card : setOfCards) {
        if (card.getSuit() == Suit::SPADES) {
            spades++;
            if (spades == 5) {
                return true;
            }
        } else if (card.getSuit() == Suit::HEARTS) {
            hearts++;
            if (hearts == 5) {
                return true;
            }
        } else if (card.getSuit() == Suit::DIAMONDS) {
            diamonds++;
            if (diamonds == 5) {
                return true;
            }
        } else {
            clubs++;
            if (clubs == 5) {
                return true;
            }
        }
    }
    return false;
}

bool Verifier::isFullHouse(std::vector<Card> setOfCards) {
    for (const auto& el : setOfCards) {
        auto found = std::search_n(rbegin(setOfCards), rend(setOfCards), 3, el);
        if (found != setOfCards.rend()) {
            setOfCards.erase(std::remove_if(setOfCards.begin(), setOfCards.end(), [&found](const auto& card) {
                                 return card.getValue() == (*found).getValue();
                             }),
                             setOfCards.end());

            if (isAPair(setOfCards)) {
                return true;
            }
        }
    }
    return false;
}

bool Verifier::isFourKind(std::vector<Card>& setOfCards) {
    for (const auto& card : setOfCards) {
        auto found = std::search_n(begin(setOfCards), end(setOfCards), 4, card);
        if (found != setOfCards.end()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isStraightFlush(std::vector<Card> setOfCards) {
    // Ace value equal 14 for hight straight
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 1].getSuit() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 2].getSuit() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 3].getSuit() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 4].getSuit()) {
            return true;
        }
    }
    // Ace value equal 1 for low straight
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getRank() == Rank::ACE) {
            setOfCards[i].setValue(1);
        }
        if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 1].getSuit() &&
            setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 2].getSuit() &&
            setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 3].getSuit() &&
            setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue() &&
            setOfCards[i].getSuit() == setOfCards[i + 4].getSuit()) {
            return true;
        }
    }
    return false;
}

bool Verifier::isRoyalFlush(const std::vector<Card>& setOfCards) {
    for (size_t i = 0; i < setOfCards.size(); ++i) {
        if (setOfCards[i].getRank() == Rank::TEN) {
            if (setOfCards[i].getValue() + 1 == setOfCards[i + 1].getValue() &&
                setOfCards[i].getSuit() == setOfCards[i + 1].getSuit() &&
                setOfCards[i].getValue() + 2 == setOfCards[i + 2].getValue() &&
                setOfCards[i].getSuit() == setOfCards[i + 2].getSuit() &&
                setOfCards[i].getValue() + 3 == setOfCards[i + 3].getValue() &&
                setOfCards[i].getSuit() == setOfCards[i + 3].getSuit() &&
                setOfCards[i].getValue() + 4 == setOfCards[i + 4].getValue() &&
                setOfCards[i].getSuit() == setOfCards[i + 4].getSuit()) {
                return true;
            }
        }
    }
    return false;
}

std::string Verifier::printPokerHand(PokerHand pokerHand) {
    switch (pokerHand) {
    case PokerHand::ROYALFLUSH:
        return "Royal flush\n";
    case PokerHand::STRAIGHTFLUSH:
        return "Straight flush\n";
    case PokerHand::FOURKIND:
        return "Four of a kind\n";
    case PokerHand::FULLHOUSE:
        return "Full house\n";
    case PokerHand::FLUSH:
        return "Flush\n";
    case PokerHand::STRAIGHT:
        return "Straight\n";
    case PokerHand::THREEKIND:
        return "Three of a kind\n";
    case PokerHand::TWOPAIRS:
        return "Two pair\n";
    case PokerHand::PAIR:
        return "Pair\n";
    case PokerHand::HIGHCARDS:
        return "High Card\n";
    default:
        return "Unknown poker hand";
    }
}
