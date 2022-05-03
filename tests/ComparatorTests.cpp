#include "gtest/gtest.h"

#include "../Comparator.hpp"
#include "../Verifier.hpp"
#include "../Card.hpp"

#include <memory>
#include <vector>

struct ComparatorTests : public ::testing::Test
{
    void SetUp() override {
        firstHand_.reserve(7);
        secondHand_.reserve(7);
    }

    std::shared_ptr<Verifier> verifier = std::make_shared<Verifier>();
    std::unique_ptr<Comparator> comparator = std::make_unique<Comparator>(verifier);

    std::vector<Card> firstHand_;
    std::vector<Card> secondHand_;
};

TEST_F(ComparatorTests, HighestCard_ShouldReturnDrawWhenHandsAreTheSame)
{
    firstHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::DRAW);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnWinWhenFirstHandIsStronger)
{
    // biggest card
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});

    // biggest card
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});
    // other cards
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});


    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnLoseWhenSecondHandIsStronger)
{
    // biggest card
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});

    // biggest card
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});
    // other cards
    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});


    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnWinWhenFirstPairIsStronger)
{
    // pair
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::FOUR, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});

    // pair
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    // other cards
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnLoseWhenSecondPairIsStronger)
{
    // pair
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::FOUR, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});

    // pair
    secondHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});
    // other cards
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnWinWhenPairsAreTheSameButFirstHandContainsHigherCard)
{
    // pair
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    // biggest card
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::FOUR, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});

    // pair
    secondHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    // biggest card
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS}); 
    // other cards
    secondHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenFirstPairFromFirstHandIsBiggerThanFirstPairFromSecondHand)
{
    // first pair
    firstHand_.push_back(Card {Rank::KING, Suit::SPADES});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});
    // second pair
    firstHand_.push_back(Card {Rank::THREE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::THREE, Suit::CLUBS});
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SIX, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnLoseWhenFirstPairFromFirstHandIsLowerThanFirstPairFromSecondHand)
{
    // first pair
    firstHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::DIAMONDS});
    // second pair
    firstHand_.push_back(Card {Rank::THREE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::THREE, Suit::CLUBS});
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SIX, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenSecondPairFromFirstHandIsBiggerThanSecondPairFromSecondHandDuringFirstPairsAreSame)
{
    // first pair
    firstHand_.push_back(Card {Rank::TEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    // second pair
    firstHand_.push_back(Card {Rank::SIX, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnLoseWhenSecondPairFromFirstHandIsLowerThanSecondPairFromSecondHandDuringFirstPairsAreSame)
{
    // first pair
    firstHand_.push_back(Card {Rank::TEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    // second pair
    firstHand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenBothPairsAreTheSameAndFirstHandContainsHigherCard)
{
    // first pair
    firstHand_.push_back(Card {Rank::TEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    // second pair
    firstHand_.push_back(Card {Rank::TWO, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    // biggest card
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS}); 
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    // biggest card
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
} 

TEST_F(ComparatorTests, Threes_ShouldReturnWinWhenFirstHandContainsHigherValueOfThree)
{
    // three
    firstHand_.push_back(Card {Rank::TEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::TEN, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    // other cards
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // three
    secondHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::DIAMONDS});
    // other cards
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::THREEKIND);
    EXPECT_EQ(secondCombination, PokerHand::THREEKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, Threes_ShouldReturnLoseWhenFirstHandContainsLowerValueOfThree)
{
    // three
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::FOUR, Suit::HEARTS});
    // other cards
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // three
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});
    // other cards
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::THREEKIND);
    EXPECT_EQ(secondCombination, PokerHand::THREEKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 

TEST_F(ComparatorTests, Straight_ShouldReturnWinWhenFirstStraightIsHigher)
{
    // straight
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::SIX, Suit::HEARTS});
    // other cards
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});

    // straight
    secondHand_.push_back(Card {Rank::ACE, Suit::SPADES});
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::THREE, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    // other cards
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::STRAIGHT);
    EXPECT_EQ(secondCombination, PokerHand::STRAIGHT);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
} 

TEST_F(ComparatorTests, Straight_ShouldReturnLoseWhenFirstStraightIsLower)
{
    // straight
    firstHand_.push_back(Card {Rank::FOUR, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::SIX, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::HEARTS});
    // other cards
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});

    // straight
    secondHand_.push_back(Card {Rank::SEVEN, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::NINE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::JACK, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::THREE, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::STRAIGHT);
    EXPECT_EQ(secondCombination, PokerHand::STRAIGHT);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, Flush_ShouldReturnWinWhenJustFirstHandContaimFiveCardsWithSameSuits)
{
    // FLUSH
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    // other cards
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});

    // other cards
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::NINE, Suit::SPADES});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::CLUBS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FLUSH);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, Flush_ShouldReturnWinWhenFirstHandContainsHighestCardDuringBothAreFlushes)
{
    // FLUSH
    firstHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    // biggest card
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});

    // other cards
    secondHand_.push_back(Card {Rank::TWO, Suit::SPADES});
    secondHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    secondHand_.push_back(Card {Rank::SIX, Suit::SPADES});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    // biggest card
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});
    // other cards
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FLUSH);
    EXPECT_EQ(secondCombination, PokerHand::FLUSH);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, FullHouses_ShouldReturnWinWhenFirstFullHouseIsBigger)
{
    // three
    firstHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    // pair
    firstHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    // other cards
    firstHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // three
    secondHand_.push_back(Card {Rank::THREE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    // pair
    secondHand_.push_back(Card {Rank::JACK, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::JACK, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FULLHOUSE);
    EXPECT_EQ(secondCombination, PokerHand::FULLHOUSE);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, FullHouses_ShouldReturnLoseWhenSecondFullHouseIsBigger)
{
    // three
    firstHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    // pair
    firstHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    // other cards
    firstHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // three
    secondHand_.push_back(Card {Rank::JACK, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::JACK, Suit::SPADES});
    // pair
    secondHand_.push_back(Card {Rank::QUEEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::SPADES});
    // other cards
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FULLHOUSE);
    EXPECT_EQ(secondCombination, PokerHand::FULLHOUSE);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, FourKind_ShouldReturnLoseWhenSecondFullHouseIsBigger)
{
    // four
    firstHand_.push_back(Card {Rank::KING, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::SPADES});
    firstHand_.push_back(Card {Rank::KING, Suit::HEARTS});

    // other cards
    firstHand_.push_back(Card {Rank::SEVEN, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::QUEEN, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS});

    // four
    secondHand_.push_back(Card {Rank::JACK, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::JACK, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    // other cards
    firstHand_.push_back(Card {Rank::SEVEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::QUEEN, Suit::SPADES});
    firstHand_.push_back(Card {Rank::ACE, Suit::SPADES});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FOURKIND);
    EXPECT_EQ(secondCombination, PokerHand::FOURKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}


