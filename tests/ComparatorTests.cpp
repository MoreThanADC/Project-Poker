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
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS}); // Biggest card in first hand

    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS}); // Biggest card in second hand

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::DRAW);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnWinWhenFirstHandIsStronger)
{
    firstHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS}); // Biggest card in first hand

    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::QUEEN, Suit::HEARTS}); // Biggest card in second hand

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnLoseWhenSecondHandIsStronger)
{
    firstHand_.push_back(Card {Rank::THREE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FOUR, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::KING, Suit::DIAMONDS}); // Biggest card in first hand

    secondHand_.push_back(Card {Rank::THREE, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FOUR, Suit::DIAMONDS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::ACE, Suit::HEARTS}); // Biggest card in second hand

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnWinWhenPairsAreTheSameButFirstHandContainsHigherCard)
{
    // pair
    firstHand_.push_back(Card {Rank::FIVE, Suit::SPADES});
    firstHand_.push_back(Card {Rank::FIVE, Suit::DIAMONDS});
    // other cards
    firstHand_.push_back(Card {Rank::FOUR, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::SEVEN, Suit::HEARTS});
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS}); // Biggest card in first hand

    // pair
    secondHand_.push_back(Card {Rank::FIVE, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::FIVE, Suit::CLUBS});
    // other cards
    secondHand_.push_back(Card {Rank::SIX, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::SEVEN, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS}); // Biggest card in second hand

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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
    // other cards
    firstHand_.push_back(Card {Rank::EIGHT, Suit::CLUBS});
    firstHand_.push_back(Card {Rank::JACK, Suit::DIAMONDS});
    firstHand_.push_back(Card {Rank::ACE, Suit::DIAMONDS}); // Biggest card in first hand

    // first pair
    secondHand_.push_back(Card {Rank::TEN, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::TEN, Suit::CLUBS});
    // second pair
    secondHand_.push_back(Card {Rank::TWO, Suit::CLUBS});
    secondHand_.push_back(Card {Rank::TWO, Suit::DIAMONDS});
    // other cards
    secondHand_.push_back(Card {Rank::EIGHT, Suit::SPADES});
    secondHand_.push_back(Card {Rank::JACK, Suit::HEARTS});
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS}); // Biggest card in second hand

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 

TEST_F(ComparatorTests, Threes_ShouldReturnWinWhenThreesAreTheSameAndFirstHandContainsHigherCard)
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
    secondHand_.push_back(Card {Rank::KING, Suit::HEARTS});

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

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

    EXPECT_EQ(firstCombination, secondCombination);

    auto settlement = comparator->settleTheTie(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 