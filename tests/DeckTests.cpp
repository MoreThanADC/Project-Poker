#include "gtest/gtest.h"

#include <algorithm>

#include "../Deck.hpp"
#include "../Card.hpp"

TEST(DeckTest, ShouldPrepareDeckWith52Cards)
{
    Deck deck {};
    EXPECT_EQ(deck.cardsInTheDeck(), 0);

    deck.setupDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 52);
}

TEST(DeckTest, WhenSetupDeckCalledMoreTimesNumberOfCardsShouldBeStill52)
{
    Deck deck {};
    EXPECT_EQ(deck.cardsInTheDeck(), 0);

    deck.setupDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 52);

    deck.setupDeck();
    deck.setupDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 52);
}

TEST(DeckTest, DecksAreNotTheSameWhenOneDeckWasShuffled)
{
    Deck deck1 {};
    deck1.setupDeck();
    Deck deck2 {};
    deck2.setupDeck();

    deck2.shuffleTheDeck();

    auto startedDeck = deck1.getDeck();
    auto shuffledDeck = deck2.getDeck();

    auto areTheSame = std::equal(startedDeck.begin(), startedDeck.end(), shuffledDeck.begin());

    EXPECT_FALSE(areTheSame);
}

TEST(DeckTest, NumberOfCardsShouldDecreaseWhenCalledTakeCardFromDeck)
{
    Deck deck {};
    deck.setupDeck();

    EXPECT_EQ(deck.cardsInTheDeck(), 52);

    deck.takeCardFromDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 51);

    deck.takeCardFromDeck();
    deck.takeCardFromDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 49);
}

TEST(DeckTest, NumberOfCardsShouldIncreaseWhenCalledReturnCardToDeck)
{
    Deck deck {};
    deck.setupDeck();

    EXPECT_EQ(deck.cardsInTheDeck(), 52);

    auto card = deck.takeCardFromDeck();
    EXPECT_EQ(deck.cardsInTheDeck(), 51);

    deck.returnCardToDeck(card);
    EXPECT_EQ(deck.cardsInTheDeck(), 52);

    //can't return to deck the same card twice
    deck.returnCardToDeck(card);
    EXPECT_EQ(deck.cardsInTheDeck(), 52);
}




