#include "Deck.hpp"

#include <string>

void Deck::setupDeck() {
    for (auto suit = static_cast<int>(Suit::SPADES) ; suit <= static_cast<int>(Suit::CLUBS) ; ++suit) {
        for (auto rank = static_cast<int>(Rank::ACE) ; rank <= static_cast<int>(Rank::KING) ; ++rank) {
            Card card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            deck_.push_back(card);
        }
    }
}

void Deck::printCards() {
    for (const auto& card : deck_) {
        std::cout << card.printRank() << " of " << card.printSuit() << '\n';
    }
};

