#include "gtest/gtest.h"

#include <memory>

#include "../Player.hpp"
#include "../Deck.hpp"
#include "../Table.hpp"

struct PlayerTest : public ::testing::Test {
    std::shared_ptr<Deck> deck_ = std::make_shared<Deck>();
    std::shared_ptr<Table> table_ = std::make_shared<Table>(deck_);
    std::shared_ptr<Player> player_ = std::make_shared<Player>(deck_, table_, "Name", 1000);
};

TEST_F(PlayerTest, ShouldTakeMaxTwoCardsFromDeckToPlayersHand)
{
    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(player_->returnNumberOfCards(), 0);
    
    player_->getCardFromDeck();
    player_->getCardFromDeck();

    EXPECT_EQ(deck_->getDeck().size(), 50);
    EXPECT_EQ(player_->returnNumberOfCards(), 2);

    player_->getCardFromDeck();
    // number of cards is still the same
    EXPECT_EQ(deck_->getDeck().size(), 50);
    EXPECT_EQ(player_->returnNumberOfCards(), 2);
}

TEST_F(PlayerTest, ShouldReturnAllCardsFromHandsToDeck)
{
    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(player_->returnNumberOfCards(), 0);
    
    player_->getCardFromDeck();
    player_->getCardFromDeck();

    EXPECT_EQ(deck_->getDeck().size(), 50);
    EXPECT_EQ(player_->returnNumberOfCards(), 2);

    player_->returnCardsToDeck();

    EXPECT_EQ(deck_->getDeck().size(), 52);
    EXPECT_EQ(player_->returnNumberOfCards(), 0);
}

TEST_F(PlayerTest, ShouldPerformBlindCorrectly)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_TRUE(player_->wasBlindCarriedOutCorrectly(100));

    EXPECT_EQ(player_->returnMoney(), 900);
    EXPECT_EQ(table_->returnPool(), 100);
}

TEST_F(PlayerTest, ShouldReturnFalseWhenPlayerIsTooPoorForBlind) 
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_FALSE(player_->wasBlindCarriedOutCorrectly(1001));

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, PlayerShouldBetAllHisMoneyWhenActionIsAllIn)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_EQ(player_->returnCurrentBet(), 0);
    table_->setCurrentBet(500);
    
    player_->allIn();

    EXPECT_EQ(player_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 1000);
    EXPECT_EQ(player_->returnCurrentBet(), 1000);
}

TEST_F(PlayerTest, PlayerCantPerformAllInWhenHisBetExceedBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
    EXPECT_EQ(player_->returnCurrentBet(), 0);

    player_->setCurrentBet(200);
    table_->setCurrentBet(200);
    
    player_->allIn();

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, PlayerShouldAllignBetToCurrentBetOnTheTableWhenActionIsCall)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(130);
    table_->setCurrentBet(200);

    EXPECT_EQ(player_->returnCurrentBet(), 130);
    EXPECT_EQ(table_->returnCurrentBet(), 200);

    player_->call();

    EXPECT_EQ(player_->returnMoney(), 930);
    EXPECT_EQ(table_->returnPool(), 70);

    EXPECT_EQ(player_->returnCurrentBet(), 200);
    EXPECT_EQ(table_->returnCurrentBet(), 200);
}

TEST_F(PlayerTest, PlayerShouldAllInWhenDontHaveEnoughMoneyToAllignBet)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(0);
    table_->setCurrentBet(1200);

    player_->call();

    EXPECT_EQ(player_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 1000);

    EXPECT_EQ(player_->returnCurrentBet(), 1000);
    EXPECT_EQ(table_->returnCurrentBet(), 1200);
}

TEST_F(PlayerTest, PlayerCantPerformCallWhenHisBetExceedMaxBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(500);
    table_->setCurrentBet(500);

    player_->call();

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_EQ(player_->returnCurrentBet(), 500);
    EXPECT_EQ(table_->returnCurrentBet(), 500);
}

TEST_F(PlayerTest, PlayerShouldBeInactiveInRundWhenActionIsFold)
{
    EXPECT_TRUE(player_->isActiveInRound());
    player_->fold();
    EXPECT_FALSE(player_->isActiveInRound());
}
