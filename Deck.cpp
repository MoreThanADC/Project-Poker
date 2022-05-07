#include "Deck.hpp"

#include <algorithm>
#include <memory>
#include <random>
#include <string>

Deck::Deck() {
    std::cout << "CREATE DECK\n";
    setupDeck();
}

void Deck::setupDeck() {
    if (deck_.size() == 0)
    {
        deck_.reserve(52);
        for (auto suit = static_cast<int>(Suit::SPADES); suit <= static_cast<int>(Suit::CLUBS); ++suit) {
            for (auto rank = static_cast<int>(Rank::ACE); rank <= static_cast<int>(Rank::KING); ++rank) {
                std::shared_ptr<Card> card = std::make_shared<Card>(static_cast<Rank>(rank), static_cast<Suit>(suit));
                deck_.push_back(card);
            }
        }
    }
}

void Deck::printCards() {
    for (const auto& card : deck_) {
        std::cout << card->printRank() << " of " << card->printSuit() << " value : " << card->printValue() << '\n';
    }
}

void Deck::shuffleTheDeck() {
    std::random_device randomDevice;
    std::mt19937 shuffleFunction(randomDevice());

    std::shuffle(begin(deck_), end(deck_), shuffleFunction);
}

std::shared_ptr<Card> Deck::takeCardFromDeck() {
    std::shared_ptr<Card> card = deck_.back();
    deck_.pop_back();

    return card;
    // TO DO: What if this function is called on empty deck? 
}

void Deck::returnCardToDeck(const std::shared_ptr<Card>& card) {
    auto isAlreadyInDeck = std::any_of(deck_.begin(), deck_.end(), [&card](auto& currentCard){
        return currentCard->getRank() == card->getRank()
            && currentCard->getSuit() == card->getSuit();
    });

    if (!isAlreadyInDeck)
    {
        deck_.push_back(card);
    }
}