#pragma once

#include <memory>

#include "Comparator.hpp"
#include "Verifier.hpp"

class Game {
public:
    Game(std::shared_ptr<Comparator> comparator) : comparator_(std::move(comparator)) {}
    bool isPlayerWinner(std::vector<Card>& firstHand, std::vector<Card>& secondHand);

private:
    std::shared_ptr<Comparator> comparator_;
};