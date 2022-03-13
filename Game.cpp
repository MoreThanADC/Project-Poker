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

void Game::performRound() {
    std::cout << "Round number: " << ++roundNumber_;
    //PREFLOP
    performPreFlop();
    displayHandsAndTable();
    performPlayerAction();
    //FLOP
    performFlop();
    displayHandsAndTable();
    performPlayerAction();
    //TURN
    performTurnOrTheRiver();
    displayHandsAndTable();
    performPlayerAction();
    //RIVER
    performTurnOrTheRiver();
    displayHandsAndTable();
}

void Game::addPlayer() {
    std::string choice;
    std::cout << "Want to add player? [y/n]: ";
    getline(std::cin, choice);
    if (choice == "y") {
        std::string name;
        std::cout << "\nName: ";
        getline(std::cin, name);

        size_t money;
        std::cout << "\nMoney: ";
        std::cin >> money;

        std::shared_ptr<Player> player = std::make_shared<Player>(table_.getDeck(), name, money);
        players_.push_back(player);
    }
}

void Game::performPreFlop() {
    for (auto& player : players_) {
        for (int i = 0; i < 2; i++) {
            player->getCardFromDeck();
        }
        table_.addToPool(player->performBlind(valueOfBlind_));
    }
}

void Game::performPlayerAction() {
    for (auto& player : players_) {
        player->displayActions();
        player->selectActions();
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

void Game::displayMoneyAndPool() const {
    for (auto& player : players_) {
        player->printMoney();
    }
    std::cout << "Money in pool: " << table_.printPool() << '\n';
}

void Game::displayHandsAndTable() const {
    for (auto& player : players_) {
        std::cout << '\n' << player->getName() << ": \n";
        player->printHand();
    }
    std::cout << "\nTable:\n";
    table_.printTable();
}