#include "gtest/gtest.h"

#include "../Verifier.hpp"
#include "../Card.hpp"

#include <memory>
#include <vector>

struct VerifierTest : public ::testing::Test
{
    void SetUp() override {
        hand_.reserve(7); // we have 5 cards in our hand, and 2 on the table
    }

    const std::unique_ptr<Verifier> verifier = std::make_unique<Verifier>();
    std::vector<Card> hand_;
};

TEST_F (VerifierTest, shouldReturBestCombinationEqualHighestCard)
{
    // highest card:
    hand_.push_back(Card {Rank::ACE, Suit::SPADES});
    // other cards:
    hand_.push_back(Card {Rank::THREE, Suit::SPADES});
    hand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    hand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::HIGHCARDS);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualPair)
{
    // pair:
    hand_.push_back(Card {Rank::TWO, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    // other cards:
    hand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    hand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::PAIR);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualTwoPair)
{
    // first pair:
    hand_.push_back(Card {Rank::TWO, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    // second pair:
    hand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    hand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    // other cards:
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::TWOPAIRS);
}


TEST_F (VerifierTest, shouldReturBestCombinationEqualThree)
{
    // three:
    hand_.push_back(Card {Rank::TWO, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    hand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    // other cards:
    hand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::THREEKIND);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualFourKinds)
{
    // four kind:
    hand_.push_back(Card {Rank::TWO, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    hand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    // other cards:
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::FOURKIND);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualFullHouse)
{
    // full house:
    hand_.push_back(Card {Rank::TWO, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    hand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::NINE, Suit::CLUBS});
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::FULLHOUSE);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualFlush)
{
    // flush:
    hand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::EIGHT, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::NINE, Suit::DIAMONDS});
    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::FLUSH);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualLowStraight)
{
    // low straight (with ACE under TWO):
    hand_.push_back(Card {Rank::ACE, Suit::SPADES});
    hand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::THREE, Suit::HEARTS});
    hand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::FIVE, Suit::SPADES});

    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::STRAIGHT);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualHighStraight)
{
    // high straight (with ACE over KING):
    hand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    hand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    hand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});
    hand_.push_back(Card {Rank::KING, Suit::SPADES});
    hand_.push_back(Card {Rank::ACE, Suit::SPADES});

    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::SIX, Suit::CLUBS});


    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::STRAIGHT);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualStraightFlush)
{
    // StraightFlush:
    hand_.push_back(Card {Rank::THREE, Suit::SPADES});
    hand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    hand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    hand_.push_back(Card {Rank::SIX, Suit::SPADES});
    hand_.push_back(Card {Rank::SEVEN, Suit::SPADES});

    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::JACK, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::STRAIGHTFLUSH);
}

TEST_F (VerifierTest, shouldReturBestCombinationEqualRoyalFlush)
{
    // royal flush
    hand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    hand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});
    hand_.push_back(Card {Rank::KING, Suit::HEARTS});
    hand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    // other cards:
    hand_.push_back(Card {Rank::TEN, Suit::SPADES});
    hand_.push_back(Card {Rank::SIX, Suit::CLUBS});

    auto result = verifier->detectBestCombination(hand_);
    EXPECT_EQ(result, PokerHand::ROYALFLUSH);
}


