#include "Game.hpp"

bool Game::isPlayerWinner(std::vector<Card>& firstHand, std::vector<Card>& secondHand) {
    auto firstCombination = comparator_->detectBestCombination(firstHand);
    auto secondCombination = comparator_->detectBestCombination(secondHand);

    if (firstCombination > secondCombination) {
        return true;
    } else if (firstCombination < secondCombination) {
        return false;
    } else {
        return comparator_->settleTheTie(firstHand, secondHand);
    }
}

void Game::performPreFlop() {
    for (auto& player : players_) {
        for (int i = 0; i < 2; i++) {
            player->getCardFromDeck();
        }
    }
}

void Game::performFlop() {
    for (int i = 0; i < 3; i++) {
        table_.addCardToTable();
    }
}

void Game::performTurnOrTheRiver() {
    table_.addCardToTable();
}