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