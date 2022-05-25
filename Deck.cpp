#include "Deck.hpp"

#include <algorithm>
#include <memory>
#include <random>
#include <ranges>
#include <string>

Deck::Deck() 
{
    setupDeck();
}

void Deck::setupDeck() 
{
    if (deck_.empty())
    {
        deck_.reserve(52);
        for (auto suit = static_cast<int>(Suit::SPADES); suit <= static_cast<int>(Suit::CLUBS); ++suit) 
        {
            for (auto rank = static_cast<int>(Rank::ACE); rank <= static_cast<int>(Rank::KING); ++rank)
            {
                auto card = Card(static_cast<Rank>(rank), static_cast<Suit>(suit));
                deck_.push_back(card);
            }
        }
    }
}

void Deck::printCards() const 
{
    for (const auto& card : deck_) {
        std::cout << card.printRank() << " of " << card.printSuit() << " value : " << card.printValue() << '\n';
    }
}

void Deck::shuffleTheDeck()
{
    std::random_device randomDevice;
    std::mt19937 shuffleFunction(randomDevice());

    std::ranges::shuffle(deck_, shuffleFunction);
}

Card Deck::takeCardFromDeck()
{
    auto card = deck_.back();
    deck_.pop_back();

    return card;
    // TO DO: What if this function is called on empty deck? 
}

void Deck::returnCardToDeck(const Card& card) 
{
    auto isAlreadyInDeck = std::ranges::any_of(deck_, [&card](const auto& currentCard){
        return currentCard.getRank() == card.getRank() 
            && currentCard.getSuit() == card.getSuit();
    });

    if (!isAlreadyInDeck)
    {
        deck_.push_back(card);
    }
}