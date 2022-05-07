#include "gtest/gtest.h"

#include <memory>

#include "../Player.hpp"
#include "../Deck.hpp"
#include "../Table.hpp"

struct PlayerTest : public ::testing::Test {
    std::shared_ptr<Deck> deck_ = std::make_shared<Deck>();
    std::shared_ptr<Table> table_ = std::make_shared<Table>(deck_);
    std::shared_ptr<Player> player_ = std::make_shared<Player>(deck_, table_, "Player", 1000);
    std::shared_ptr<Player> poorPlayer_ = std::make_shared<Player>(deck_, table_, "Bankrupt", 0);
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
    EXPECT_EQ(poorPlayer_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_FALSE(poorPlayer_->wasBlindCarriedOutCorrectly(100));

    EXPECT_EQ(poorPlayer_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, AllIn_PlayerShouldBetAllHisMoney)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_EQ(player_->returnCurrentBet(), 0);
    table_->setCurrentBet(500);
    
    EXPECT_TRUE(player_->allIn());

    EXPECT_EQ(player_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 1000);
    EXPECT_EQ(player_->returnCurrentBet(), 1000);
}

TEST_F(PlayerTest, AllIn_PlayerCantPerformThisActionWhenHisBetExceedBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
    EXPECT_EQ(player_->returnCurrentBet(), 0);

    player_->setCurrentBet(200);
    table_->setCurrentBet(200);
    
    EXPECT_FALSE(player_->allIn());

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, AllIn_PlayerCantPerformThisActionWhenDontHaveMoney)
{
    EXPECT_EQ(poorPlayer_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_FALSE(poorPlayer_->allIn());

    EXPECT_EQ(poorPlayer_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, Call_PlayerShouldAllignBetToCurrentBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(130);
    table_->setCurrentBet(200);

    EXPECT_EQ(player_->returnCurrentBet(), 130);
    EXPECT_EQ(table_->returnCurrentBet(), 200);

    EXPECT_TRUE(player_->call());

    EXPECT_EQ(player_->returnMoney(), 930);
    EXPECT_EQ(table_->returnPool(), 70);

    EXPECT_EQ(player_->returnCurrentBet(), 200);
    EXPECT_EQ(table_->returnCurrentBet(), 200);
}

TEST_F(PlayerTest, Call_PlayerShouldPerformAllInWhenDontHaveEnoughMoneyToAllignBet)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(0);
    table_->setCurrentBet(1200);

    EXPECT_TRUE(player_->call());

    EXPECT_EQ(player_->returnMoney(), 0);
    EXPECT_EQ(table_->returnPool(), 1000);

    EXPECT_EQ(player_->returnCurrentBet(), 1000);
    EXPECT_EQ(table_->returnCurrentBet(), 1200);
}

TEST_F(PlayerTest, Call_PlayerCantPerformThisActionWhenHisBetExceedMaxBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(500);
    table_->setCurrentBet(500);

    EXPECT_FALSE(player_->call());

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_EQ(player_->returnCurrentBet(), 500);
    EXPECT_EQ(table_->returnCurrentBet(), 500);
}

TEST_F(PlayerTest, Fold_PlayerShouldBeSetAsInactiveInRund)
{
    EXPECT_TRUE(player_->isActiveInRound());
    EXPECT_TRUE(player_->fold());
    EXPECT_FALSE(player_->isActiveInRound());
}

TEST_F(PlayerTest, Bet_PlayerShoulBetCorrectly)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(0);
    table_->setCurrentBet(0);

    EXPECT_TRUE(player_->performBet(300));

    EXPECT_EQ(player_->returnMoney(), 700);
    EXPECT_EQ(table_->returnPool(), 300);

    EXPECT_EQ(player_->returnCurrentBet(), 300);
    EXPECT_EQ(table_->returnCurrentBet(), 300);
}

TEST_F(PlayerTest, Bet_PlayerShoulBetCorrectly_2)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(0);
    table_->setCurrentBet(400);

    EXPECT_TRUE(player_->performBet(500));

    EXPECT_EQ(player_->returnMoney(), 500);
    EXPECT_EQ(table_->returnPool(), 500);

    EXPECT_EQ(player_->returnCurrentBet(), 500);
    EXPECT_EQ(table_->returnCurrentBet(), 500);
}

TEST_F(PlayerTest, Bet_PlayerShoulBetCorrectly_3)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(100);
    table_->setCurrentBet(400);

    EXPECT_TRUE(player_->performBet(600));

    EXPECT_EQ(player_->returnMoney(), 500);
    EXPECT_EQ(table_->returnPool(), 500);

    EXPECT_EQ(player_->returnCurrentBet(), 600);
    EXPECT_EQ(table_->returnCurrentBet(), 600);
}

TEST_F(PlayerTest, Bet_PlayerCantBetMoreThanHeHasMoney)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    EXPECT_FALSE(player_->performBet(1300));

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
}

TEST_F(PlayerTest, Bet_PlayerCantBetLessThanActualBetOnTheTable)
{
    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);

    player_->setCurrentBet(300);
    table_->setCurrentBet(500);

    EXPECT_FALSE(player_->performBet(400));

    EXPECT_EQ(player_->returnMoney(), 1000);
    EXPECT_EQ(table_->returnPool(), 0);
}