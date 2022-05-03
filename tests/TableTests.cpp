#include "gtest/gtest.h"

#include <memory>

#include "../Deck.hpp"
#include "../Table.hpp"

struct TableTest : public ::testing::Test
{
    std::shared_ptr<Deck> deck_ = std::make_shared<Deck>();
    std::shared_ptr<Table> table_ = std::make_shared<Table>(deck_); 
};

TEST_F(TableTest, ShouldMoveMaxFiveCardsFromDeckToTable)
{
    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(table_->returnNumberOfCards(), 0);

    for (size_t i = 0; i < 5; i++) {
        table_->addCardToTable();
    }

    EXPECT_EQ(deck_->getDeck().size(), 47);
    EXPECT_EQ(table_->returnNumberOfCards(), 5);

    table_->addCardToTable();
    
    // number of cards is still the same
    EXPECT_EQ(deck_->getDeck().size(), 47);
    EXPECT_EQ(table_->returnNumberOfCards(), 5);
}

TEST_F(TableTest, ShouldReturnAllCardsFromTableToDeck)
{
    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(table_->returnNumberOfCards(), 0);

    for (size_t i = 0; i < 5; i++) {
        table_->addCardToTable();
    }

    EXPECT_EQ(deck_->getDeck().size(), 47);
    EXPECT_EQ(table_->returnNumberOfCards(), 5);

    table_->returnCardsToDeck();

    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(table_->returnNumberOfCards(), 0);
}