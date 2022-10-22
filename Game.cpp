#include "Game.hpp"

#include <algorithm>
#include <ranges>
#include <stdlib.h>

namespace
{

std::string inputPlayerName()
{
    std::cout << "Name ";
    std::string name;
    std::cin.ignore();
    getline(std::cin, name);

    return name;
}

} // namespace

Game::Game()
{
    verifier_ = std::make_shared<Verifier>();
    comparator_ = std::make_unique<Comparator>(verifier_);
    deck_ = std::make_shared<Deck>();
    table_ = std::make_shared<Table>(deck_);

    players_.push_back(std::make_shared<Player>(deck_, table_, "Player", 2000));
    players_.push_back(std::make_shared<Player>(deck_, table_, "Computer", 200));
}

void Game::startGame() 
{
    while (true) 
    {
        prepareDeck();
        printOperations();
        selectOperation();
    }
}

void Game::performRound()
{
    activatePlayers();
    if (!arePlayersActive())
    {
        std::cout << "Players are not ready!\n";
        return;
    }

    roundNumber_++;
    std::cout << "\nROUND NUMBER " << roundNumber_ << "\n\n";
    // BLIND
    performBlind();
    //PREFLOP
    performPreFlop();
    prepareCardsForVerdict();
    setBestCombinations();
    displayHandsAndTable();
    performPlayerAction();
    //FLOP
    performFlop();
    prepareCardsForVerdict();
    setBestCombinations();
    displayHandsAndTable();
    if (arePlayersActive())
    {
        performPlayerAction();
    }
    //TURN
    performTurnOrTheRiver();
    prepareCardsForVerdict();
    setBestCombinations();
    displayHandsAndTable();
    if (arePlayersActive())
    {
        performPlayerAction();
    }
    //RIVER
    performTurnOrTheRiver();
    prepareCardsForVerdict();
    setBestCombinations();
    displayHandsAndTable();
    //VERDICT
    prepareCardsForVerdict();
    setBestCombinations();
    sortPlayersByHand();
    printWinner();
    payOutForWinners();
}

bool Game::isTieAmongWinners()
{
    return comparator_->calculateBetterHand(players_[0]->getHandToEvaluate(), players_[1]->getHandToEvaluate()) == Settlement::DRAW;
}

void Game::payOutForWinners()
{
    size_t value = table_->getPool();
    if (isTieAmongWinners())
    {
        const size_t numberOfWinners = 2;
        value = table_->getPool() / numberOfWinners;

        players_[0]->addToAccount(value);
        players_[1]->addToAccount(value);
    }
    else
    {
        players_[0]->addToAccount(value);
    }

    table_->resetPool();
}

void Game::sortPlayersByHand()
{
    std::ranges::sort(players_, [this](auto& firstPlayer, auto& secondPlayer){
        return comparator_->calculateBetterHand(firstPlayer->getHandToEvaluate(), secondPlayer->getHandToEvaluate()) == Settlement::WIN;
    });
}

void Game::prepareCardsForVerdict() const
{
    for (const auto& player : players_)
    {
        player->prepareCardsForVerdict();
    }
}

void Game::setBestCombinations() const
{
    for (const auto& player : players_)
    {
        player->setBestCombination(verifier_->detectBestCombination(player->getHandToEvaluate()));
    }
}

void Game::activatePlayers()
{
    for (const auto& player : players_)
    {
        if (player->getMoney() >= valueOfBlind_ && !player->isActiveInRound())
        {
            player->setPlayerActivity(true);
        }
        else if (player->getMoney() < valueOfBlind_)
        {
            removePlayer(player->getName());
        }
    }
}

bool Game::arePlayersActive() const
{
    size_t numberOfActivePlayers = std::ranges::count_if(players_, [](const auto& player){
        return player->isActiveInRound();
    });

    return numberOfActivePlayers > 1;
}

void Game::performBlind() const
{
    for (const auto& player : players_)
    {
        player->performBlind(valueOfBlind_);
    }
}

void Game::selectOperation()
{
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

void Game::printOperations() const
{
    std::cout << "1. Perform round\n";
    std::cout << "2. Add player\n";
    std::cout << "3. Remove player\n";
    std::cout << "4. Print players\n";
    std::cout << "0. Exit\n";
    std::cout << "Select action: ";
}

void Game::addPlayer()
{
    if (players_.size() < maxNumberOfPlayers_)
    {
        const auto name = inputPlayerName();

        auto found = std::ranges::find_if(players_, [&name](const auto& player){
            return name == player->getName();
        });

        if (found != players_.end())
        {
            std::cout << "Player with this name already exist\n";
            return;
        }

        size_t money;
        std::cout << "Money: ";
        std::cin >> money;

        if (money < valueOfBlind_)
        {
            std::cout << "Value to low. The player has no money to bet\n";
            return;
        }

        std::cout << "Added " << name << ", with " << money << " coins.\n";

        auto player = std::make_shared<Player>(deck_, table_, name, money);
        players_.push_back(player);
    } 
    else
    {
        std::cout << "Number of players can't exceed " << maxNumberOfPlayers_ << '\n';
    }
}

void Game::removePlayer()
{
    removePlayer(inputPlayerName());
}

void Game::removePlayer(const std::string& name)
{
    auto removedPlayer = std::ranges::find_if(players_, [&name](const auto& player){
        return name == player->getName();
    });

    if (removedPlayer != players_.end())
    {
        std::iter_swap(removedPlayer, players_.end() - 1);
        players_.pop_back();
        std::cout << "Player removed\n";
    }
    else 
    {
        std::cout << "Player not found\n";
    }
}

void Game::performPlayerAction() const
{
    for (const auto& player : players_)
    {
        if (player->isActiveInRound())
        {
            player->selectActions();
        }
    }
}

void Game::performPreFlop()
{
    const size_t amountOfCardsToBeLaid = 2;
    for (const auto& player : players_)
    {
        for (size_t i = 0; i < amountOfCardsToBeLaid; i++)
        {
            player->getCardFromDeck();
        }
    }
}

void Game::performFlop() const
{
    const size_t amountOfCardsToBeLaid = 3;
    for (size_t i = 0; i < amountOfCardsToBeLaid; i++)
    {
        table_->addCardToTable();
    }
}

void Game::performTurnOrTheRiver() const
{
    table_->addCardToTable();
}

void Game::prepareDeck() const
{
    if (roundNumber_ > 0)
    {
        returnCardsFromPlayers();
        returnCardsFromTable();
    }
    deck_->shuffleTheDeck();
}

void Game::returnCardsFromPlayers() const
{
    for (const auto& player : players_)
    {
        player->returnCardsToDeck();
    }
}

void Game::returnCardsFromTable() const
{
    table_->returnCardsToDeck();
}

void Game::printPlayers() const
{
    std::cout << "\nList of players:\n";
    for (const auto& player : players_)
    {
        std::cout << player->getName() << ' ' <<  player->getMoney() << '$'<< '\n';
    }
    std::cout << '\n';
}

void Game::displayHandsAndTable() const
{
    for (const auto& player : players_)
    {
        std::cout << player->getName() << " [" << player->getMoney() << "$]";
        player->isActiveInRound() ? std::cout << " [active]" : std::cout << " [inactive]";  
        std::cout << " [" << verifier_->printPokerHand(player->getBestCombination()) << "]\n";
        player->printHand();
        std::cout << '\n';
    }
    table_->printTable();
}

void Game::printWinner()
{
    if (isTieAmongWinners())
    {
        std::cout << players_[0]->getName() << " and " << players_[1]->getName() << " are the winners!\n";
        std::cout << "BEST COMBINATION: " << verifier_->printPokerHand(players_[0]->getBestCombination()) << '\n';
        std::cout << "PRIZE: " << table_->getPool() / 2 << "\n\n";
    }
    else
    {
        std::cout << players_[0]->getName() << " is the winner!\n";
        std::cout << "BEST COMBINATION: " << verifier_->printPokerHand(players_[0]->getBestCombination()) << '\n';
        std::cout << "PRIZE: " << table_->getPool() << "\n\n";
    }
}