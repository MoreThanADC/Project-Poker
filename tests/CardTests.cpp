#include "gtest/gtest.h"

#include "../Card.hpp"

TEST(CardTest, shouldReturnAppropriateValueForCard)
{
    Card two(Rank::TWO, Suit::SPADES);
    EXPECT_EQ(two.getValue(), 2);

    Card three(Rank::THREE, Suit::SPADES);
    EXPECT_EQ(three.getValue(), 3);

    Card four(Rank::FOUR, Suit::SPADES);
    EXPECT_EQ(four.getValue(), 4);

    Card five(Rank::FIVE, Suit::SPADES);
    EXPECT_EQ(five.getValue(), 5);

    Card six(Rank::SIX, Suit::SPADES);
    EXPECT_EQ(six.getValue(), 6);

    Card seven(Rank::SEVEN, Suit::SPADES);
    EXPECT_EQ(seven.getValue(), 7);

    Card eight(Rank::EIGHT, Suit::SPADES);
    EXPECT_EQ(eight.getValue(), 8);

    Card nine(Rank::NINE, Suit::SPADES);
    EXPECT_EQ(nine.getValue(), 9);

    Card ten(Rank::TEN, Suit::SPADES);
    EXPECT_EQ(ten.getValue(), 10);

    Card jack(Rank::JACK, Suit::SPADES);
    EXPECT_EQ(jack.getValue(), 11);

    Card queen(Rank::QUEEN, Suit::SPADES);
    EXPECT_EQ(queen.getValue(), 12);

    Card king(Rank::KING, Suit::SPADES);
    EXPECT_EQ(king.getValue(), 13);
    
    Card ace(Rank::ACE, Suit::SPADES);
    EXPECT_EQ(ace.getValue(), 14);
}