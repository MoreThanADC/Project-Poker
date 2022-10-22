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
    firstHand_ = {  {Rank::THREE, Suit::SPADES},
                    {Rank::FOUR,  Suit::SPADES},
                    {Rank::FIVE,  Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK,  Suit::DIAMONDS},
                    {Rank::ACE,   Suit::DIAMONDS}};

    secondHand_ = { {Rank::THREE, Suit::DIAMONDS},
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::JACK, Suit::HEARTS},
                    {Rank::ACE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::DRAW);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnWinWhenFirstHandIsStronger)
{
    firstHand_ = {  {Rank::KING, Suit::DIAMONDS},  // HIGHEST CARD
                    {Rank::THREE, Suit::SPADES},
                    {Rank::FOUR, Suit::SPADES},
                    {Rank::FIVE, Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS}};

    secondHand_ = { {Rank::QUEEN, Suit::HEARTS},   // HIGHEST CARD
                    {Rank::TWO, Suit::DIAMONDS},
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::TEN, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, HighestCard_ShouldReturnLoseWhenSecondHandIsStronger)
{
    firstHand_ = {  {Rank::KING, Suit::DIAMONDS},  // HIGHEST CARD
                    {Rank::THREE, Suit::SPADES},
                    {Rank::FOUR, Suit::SPADES},
                    {Rank::FIVE, Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS}};

    secondHand_ = { {Rank::ACE, Suit::HEARTS},     // HIGHEST CARD
                    {Rank::TWO, Suit::DIAMONDS},
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::TEN, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::HIGHCARDS);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnWinWhenFirstPairIsStronger)
{
    firstHand_ = {  {Rank::FIVE, Suit::SPADES},   // PAIR
                    {Rank::FIVE, Suit::DIAMONDS}, // PAIR
                    {Rank::FOUR, Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};

    secondHand_ = { {Rank::TWO, Suit::DIAMONDS},   // PAIR
                    {Rank::TWO, Suit::CLUBS},      // PAIR
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::TEN, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnLoseWhenSecondPairIsStronger)
{
    firstHand_ = {  {Rank::FIVE, Suit::SPADES},      // PAIR
                    {Rank::FIVE, Suit::DIAMONDS},    // PAIR
                    {Rank::FOUR, Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};

    secondHand_ = { {Rank::QUEEN, Suit::DIAMONDS},   // PAIR
                    {Rank::QUEEN, Suit::CLUBS},      // PAIR
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::TEN, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, OnePair_ShouldReturnWinWhenPairsAreTheSameButFirstHandContainsHigherCard)
{
    firstHand_ = {  {Rank::QUEEN, Suit::SPADES},     // PAIR
                    {Rank::QUEEN, Suit::DIAMONDS},   // PAIR
                    {Rank::FOUR, Suit::HEARTS},
                    {Rank::SEVEN, Suit::HEARTS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};    // HIGHEST CARD

    secondHand_ = { {Rank::QUEEN, Suit::HEARTS},     // PAIR
                    {Rank::QUEEN, Suit::CLUBS},      // PAIR
                    {Rank::FOUR, Suit::DIAMONDS},
                    {Rank::FIVE, Suit::CLUBS},
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::KING, Suit::HEARTS}};     // HIGHEST CARD

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::PAIR);
    EXPECT_EQ(secondCombination, PokerHand::PAIR);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenFirstPairFromFirstHandIsBiggerThanFirstPairFromSecondHand)
{
    firstHand_ = {  {Rank::KING, Suit::SPADES},      // FIRST PAIR
                    {Rank::KING, Suit::DIAMONDS},    // FIRST PAIR
                    {Rank::THREE, Suit::HEARTS},     // SECOND PAIR
                    {Rank::THREE, Suit::CLUBS},      // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::QUEEN, Suit::HEARTS},     // FIRST PAIR
                    {Rank::QUEEN, Suit::CLUBS},      // FIRST PAIR
                    {Rank::SIX, Suit::DIAMONDS},     // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::KING, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnLoseWhenFirstPairFromFirstHandIsLowerThanFirstPairFromSecondHand)
{
    firstHand_ = {  {Rank::QUEEN, Suit::SPADES},     // FIRST PAIR
                    {Rank::QUEEN, Suit::DIAMONDS},   // FIRST PAIR
                    {Rank::THREE, Suit::HEARTS},     // SECOND PAIR
                    {Rank::THREE, Suit::CLUBS},      // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::KING, Suit::HEARTS},      // FIRST PAIR
                    {Rank::KING, Suit::CLUBS},       // FIRST PAIR
                    {Rank::SIX, Suit::DIAMONDS},     // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::ACE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenSecondPairFromFirstHandIsBiggerThanSecondPairFromSecondHandDuringFirstPairsAreSame)
{
    firstHand_ = {  {Rank::KING, Suit::SPADES},      // FIRST PAIR
                    {Rank::KING, Suit::DIAMONDS},    // FIRST PAIR
                    {Rank::SEVEN, Suit::HEARTS},     // SECOND PAIR
                    {Rank::SEVEN, Suit::CLUBS},      // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::KING, Suit::HEARTS},      // FIRST PAIR
                    {Rank::KING, Suit::CLUBS},       // FIRST PAIR
                    {Rank::SIX, Suit::DIAMONDS},     // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::SEVEN, Suit::CLUBS},
                    {Rank::EIGHT, Suit::SPADES},
                    {Rank::ACE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}   

TEST_F(ComparatorTests, TwoPairs_ShouldReturnLoseWhenSecondPairFromFirstHandIsLowerThanSecondPairFromSecondHandDuringFirstPairsAreSame)
{
    firstHand_ = {  {Rank::KING, Suit::SPADES},      // FIRST PAIR
                    {Rank::KING, Suit::DIAMONDS},    // FIRST PAIR
                    {Rank::SIX, Suit::HEARTS},       // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::KING, Suit::HEARTS},      // FIRST PAIR
                    {Rank::KING, Suit::CLUBS},       // FIRST PAIR
                    {Rank::SEVEN, Suit::DIAMONDS},   // SECOND PAIR
                    {Rank::SEVEN, Suit::CLUBS},      // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::NINE, Suit::SPADES},
                    {Rank::ACE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 

TEST_F(ComparatorTests, TwoPairs_ShouldReturnWinWhenBothPairsAreTheSameAndFirstHandContainsHigherCard)
{
    firstHand_ = {  {Rank::KING, Suit::SPADES},      // FIRST PAIR
                    {Rank::KING, Suit::DIAMONDS},    // FIRST PAIR
                    {Rank::SIX, Suit::HEARTS},       // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};    // HIGHEST CARD

    secondHand_ = { {Rank::KING, Suit::HEARTS},      // FIRST PAIR
                    {Rank::KING, Suit::CLUBS},       // FIRST PAIR
                    {Rank::SIX, Suit::DIAMONDS},     // SECOND PAIR
                    {Rank::SIX, Suit::CLUBS},        // SECOND PAIR
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::NINE, Suit::SPADES},
                    {Rank::QUEEN, Suit::HEARTS}};    // HIGHEST CARD

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::TWOPAIRS);
    EXPECT_EQ(secondCombination, PokerHand::TWOPAIRS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
} 

TEST_F(ComparatorTests, Threes_ShouldReturnWinWhenFirstHandContainsHigherValueOfThree)
{
    firstHand_ = {  {Rank::TEN, Suit::SPADES},       // THREE
                    {Rank::TEN, Suit::DIAMONDS},     // THREE
                    {Rank::TEN, Suit::HEARTS},       // THREE
                    {Rank::SIX, Suit::CLUBS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::TWO, Suit::HEARTS},       // THREE
                    {Rank::TWO, Suit::CLUBS},        // THREE
                    {Rank::TWO, Suit::DIAMONDS},     // THREE
                    {Rank::SIX, Suit::CLUBS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::NINE, Suit::SPADES},
                    {Rank::KING, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::THREEKIND);
    EXPECT_EQ(secondCombination, PokerHand::THREEKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, Threes_ShouldReturnLoseWhenFirstHandContainsLowerValueOfThree)
{
    firstHand_ = {  {Rank::TEN, Suit::SPADES},       // THREE
                    {Rank::TEN, Suit::DIAMONDS},     // THREE
                    {Rank::TEN, Suit::HEARTS},       // THREE
                    {Rank::SIX, Suit::CLUBS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { {Rank::ACE, Suit::HEARTS},       // THREE
                    {Rank::ACE, Suit::CLUBS},        // THREE
                    {Rank::ACE, Suit::DIAMONDS},     // THREE
                    {Rank::SIX, Suit::CLUBS},
                    {Rank::EIGHT, Suit::CLUBS},
                    {Rank::NINE, Suit::SPADES},
                    {Rank::KING, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::THREEKIND);
    EXPECT_EQ(secondCombination, PokerHand::THREEKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
} 

TEST_F(ComparatorTests, Straight_ShouldReturnWinWhenFirstStraightIsHigher)
{
    firstHand_ = {  {Rank::TWO, Suit::SPADES},       // STRAIGHT
                    {Rank::THREE, Suit::DIAMONDS},   // STRAIGHT
                    {Rank::FOUR, Suit::HEARTS},      // STRAIGHT
                    {Rank::FIVE, Suit::CLUBS},       // STRAIGHT
                    {Rank::SIX, Suit::CLUBS},        // STRAIGHT
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};

    secondHand_ = { {Rank::ACE, Suit::HEARTS},       // STRAIGHT
                    {Rank::TWO, Suit::CLUBS},        // STRAIGHT
                    {Rank::THREE, Suit::DIAMONDS},   // STRAIGHT
                    {Rank::FOUR, Suit::CLUBS},       // STRAIGHT
                    {Rank::FIVE, Suit::CLUBS},       // STRAIGHT
                    {Rank::JACK, Suit::SPADES},
                    {Rank::KING, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::STRAIGHT);
    EXPECT_EQ(secondCombination, PokerHand::STRAIGHT);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
} 

TEST_F(ComparatorTests, Straight_ShouldReturnLoseWhenFirstStraightIsLower)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // STRAIGHT
                    {Rank::FIVE, Suit::DIAMONDS},    // STRAIGHT
                    {Rank::SIX, Suit::HEARTS},       // STRAIGHT
                    {Rank::SEVEN, Suit::CLUBS},      // STRAIGHT
                    {Rank::EIGHT, Suit::CLUBS},      // STRAIGHT
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};

    secondHand_ = { {Rank::TEN, Suit::HEARTS},       // STRAIGHT
                    {Rank::JACK, Suit::CLUBS},       // STRAIGHT
                    {Rank::QUEEN, Suit::DIAMONDS},   // STRAIGHT
                    {Rank::KING, Suit::CLUBS},       // STRAIGHT
                    {Rank::ACE, Suit::CLUBS},        // STRAIGHT
                    {Rank::TWO, Suit::SPADES},
                    {Rank::THREE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::STRAIGHT);
    EXPECT_EQ(secondCombination, PokerHand::STRAIGHT);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, Flush_ShouldReturnWinWhenJustFirstHandContainsFiveCardsWithSameSuits)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // FLUSH
                    {Rank::FIVE, Suit::SPADES},      // FLUSH
                    {Rank::SIX, Suit::SPADES},       // FLUSH
                    {Rank::SEVEN, Suit::SPADES},     // FLUSH
                    {Rank::TEN, Suit::SPADES},       // FLUSH
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};

    secondHand_ = { {Rank::NINE, Suit::HEARTS},   
                    {Rank::JACK, Suit::CLUBS},   
                    {Rank::QUEEN, Suit::DIAMONDS},
                    {Rank::KING, Suit::CLUBS},  
                    {Rank::ACE, Suit::CLUBS},
                    {Rank::TWO, Suit::SPADES},
                    {Rank::THREE, Suit::HEARTS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FLUSH);
    EXPECT_EQ(secondCombination, PokerHand::HIGHCARDS);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, Flush_ShouldReturnWinWhenFirstHandContainsHighestCardDuringBothAreFlushes)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // FLUSH
                    {Rank::FIVE, Suit::SPADES},      // FLUSH
                    {Rank::SIX, Suit::SPADES},       // FLUSH
                    {Rank::SEVEN, Suit::SPADES},     // FLUSH
                    {Rank::ACE, Suit::SPADES},       // FLUSH
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};    // HIGHEST CARD

    secondHand_ = { {Rank::FIVE, Suit::HEARTS},      // FLUSH
                    {Rank::NINE, Suit::HEARTS},      // FLUSH
                    {Rank::JACK, Suit::HEARTS},      // FLUSH
                    {Rank::QUEEN, Suit::HEARTS},     // FLUSH
                    {Rank::THREE, Suit::HEARTS},     // FLUSH
                    {Rank::TWO, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS}};   // HIGHEST CARD


    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FLUSH);
    EXPECT_EQ(secondCombination, PokerHand::FLUSH);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, FullHouses_ShouldReturnWinWhenFirstFullHouseIsBigger)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // FULLHOUSE
                    {Rank::FOUR, Suit::DIAMONDS},    // FULLHOUSE
                    {Rank::FOUR, Suit::HEARTS},      // FULLHOUSE
                    {Rank::SEVEN, Suit::HEARTS},     // FULLHOUSE
                    {Rank::SEVEN, Suit::SPADES},     // FULLHOUSE
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { 
                    {Rank::TWO, Suit::SPADES},       // FULLHOUSE
                    {Rank::TWO, Suit::HEARTS},       // FULLHOUSE
                    {Rank::TWO, Suit::DIAMONDS},     // FULLHOUSE
                    {Rank::QUEEN, Suit::HEARTS},     // FULLHOUSE
                    {Rank::QUEEN, Suit::DIAMONDS},   // FULLHOUSE
                    {Rank::KING, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FULLHOUSE);
    EXPECT_EQ(secondCombination, PokerHand::FULLHOUSE);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::WIN);
}

TEST_F(ComparatorTests, FullHouses_ShouldReturnLoseWhenSecondFullHouseIsBigger)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // FULLHOUSE
                    {Rank::FOUR, Suit::DIAMONDS},    // FULLHOUSE
                    {Rank::FOUR, Suit::HEARTS},      // FULLHOUSE
                    {Rank::SEVEN, Suit::HEARTS},     // FULLHOUSE
                    {Rank::SEVEN, Suit::SPADES},     // FULLHOUSE
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { 
                    {Rank::FOUR, Suit::SPADES},      // FULLHOUSE
                    {Rank::FOUR, Suit::HEARTS},      // FULLHOUSE
                    {Rank::FOUR, Suit::DIAMONDS},    // FULLHOUSE
                    {Rank::QUEEN, Suit::HEARTS},     // FULLHOUSE
                    {Rank::QUEEN, Suit::DIAMONDS},   // FULLHOUSE
                    {Rank::KING, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FULLHOUSE);
    EXPECT_EQ(secondCombination, PokerHand::FULLHOUSE);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}

TEST_F(ComparatorTests, FourKind_ShouldReturnLoseWhenSecondFourKindBigger)
{
    firstHand_ = {  {Rank::FOUR, Suit::SPADES},      // FOURKIND
                    {Rank::FOUR, Suit::DIAMONDS},    // FOURKIND
                    {Rank::FOUR, Suit::HEARTS},      // FOURKIND
                    {Rank::FOUR, Suit::CLUBS},       // FOURKIND
                    {Rank::SEVEN, Suit::SPADES},
                    {Rank::JACK, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    secondHand_ = { 
                    {Rank::QUEEN, Suit::SPADES},      // FOURKIND
                    {Rank::QUEEN, Suit::HEARTS},      // FOURKIND
                    {Rank::QUEEN, Suit::DIAMONDS},    // FOURKIND
                    {Rank::QUEEN, Suit::CLUBS},       // FOURKIND
                    {Rank::TWO, Suit::DIAMONDS},
                    {Rank::KING, Suit::DIAMONDS},
                    {Rank::ACE, Suit::DIAMONDS}};

    auto firstCombination = verifier->detectBestCombination(firstHand_);
    auto secondCombination = verifier->detectBestCombination(secondHand_);

    EXPECT_EQ(firstCombination, PokerHand::FOURKIND);
    EXPECT_EQ(secondCombination, PokerHand::FOURKIND);

    auto settlement = comparator->calculateBetterHand(firstHand_, secondHand_);

    EXPECT_EQ(settlement, Settlement::LOSE);
}


