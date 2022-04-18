#include "Game.hpp"

#include <stdlib.h>
#include <algorithm>

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
    std::cout << "\nINITIAL NUMBER OF CARDS IN THE DECK: " << table_.getDeck()->cardsInTheDeck() << '\n';
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

void Game::startGame() {
    while (true) {
        prepareDeck();
        printOperations();
        selectOperation();
    }
}

void Game::selectOperation() {
    int choice;
    do {
        std::cin >> choice;
        switch(choice) {
        case 1 : performRound();
            break;
        case 2 : addPlayer();
            break;
        case 3 : removePlayer();
            break;
        case 4 : printPlayers();
            break;
        case 0 : exit(0);
        default : 
            std::cout << "Wrong choice, try again.\n";
        }
    }
    while (choice < 1 || choice > 4 );
}

void Game::printOperations() const {
    std::cout << "1. Perform round\n";
    std::cout << "2. Add player\n";
    std::cout << "3. Remove player\n";
    std::cout << "4. Print player\n";
    std::cout << "0. Exit\n";
    std::cout << "Select action: ";
}

void Game::addPlayer() {
    if (players_.size() < maxNumberOfPlayers_) {
        std::string name;
        std::cout << "\nName: ";
        std::cin.ignore();
        getline(std::cin, name);

        auto found = std::find_if(players_.begin(), players_.end(), [&name](const auto& player){
            return name == player->getName();
        });

        if (found != players_.end()) {
            std::cout << "This name is taken\n";
            return;
        }

        size_t money;
        std::cout << "Money: ";
        std::cin >> money;

        if (money < valueOfBlind_) {
            std::cout << "Value to low. The player has no money to bet\n";
            return;
        }

        std::cout << "Added " << name << ", with " << money << " coins.\n";

        std::shared_ptr<Player> player = std::make_shared<Player>(table_.getDeck(), name, money);
        players_.push_back(player);
    } else {
        std::cout << "Number of players can't exceed " << maxNumberOfPlayers_ << '\n';
    }
}

void Game::removePlayer() {
    std::cout << "player's name to delete: ";
    std::string name;
    std::cin.ignore();
    getline(std::cin, name);

    auto found = std::find_if(players_.begin(), players_.end(), [&name](const auto& player) {
        return name == player->getName();
    });
    
    if (found != std::end(players_)) {
        players_.erase(found, players_.end());
        std::cout << "Player removed\n";
    } else {
        std::cout << "Player not found\n";
    }
}

void Game::performPlayerAction() {
    for (auto& player : players_) {
        player->displayActions();
        player->selectActions();
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

void Game::performFlop() {
    for (int i = 0; i < 3; i++) {
        table_.addCardToTable();
    }
}

void Game::performTurnOrTheRiver() {
    table_.addCardToTable();
}

void Game::prepareDeck() {
    if (roundNumber_ == 0) {
        table_.getDeck()->setupDeck();
    } else {
        returnPlayersCards();
        returnCardsFromTable();
    }
    table_.getDeck()->shuffleTheDeck();
}

void Game::returnPlayersCards() {
    for (auto& player : players_) {
        player->returnCardsToDeck();
    }
}

void Game::returnCardsFromTable() {
    table_.returnCardsToDeck();
}


void Game::printPlayers() {
    for (size_t i = 0; i < players_.size(); i++) {
        std::cout << i + 1 << ". ";
        players_[i]->printMoney();
    }
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