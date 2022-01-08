#include "Deck.hpp"

void Deck::setupDeck() {
    for (auto suit = static_cast<int>(Suit::SPADES) ; suit <= static_cast<int>(Suit::SPADES) ; ++suit) {
        for (auto rank = static_cast<int>(Rank::ACE) ; rank <= static_cast<int>(Rank::KING) ; ++rank) {
            Card card(static_cast<Rank>(rank), static_cast<Suit>(suit));
            deck_.push_back(card);
        }
    }
}