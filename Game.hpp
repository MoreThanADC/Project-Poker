#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "Comparator.hpp"
#include "Verifier.hpp"
#include "Table.hpp"
#include "Player.hpp"

class Game 
{
public:
    Game();

    void startGame();

private:
    void selectOperation();
    void printOperations() const;

    void addPlayer();
    void removePlayer(const std::string& name);
    void removePlayer();

    void performRound();
    void performPlayerAction() const;
    void performPreFlop();
    void performFlop() const;
    void performTurnOrTheRiver() const;

    void prepareDeck() const;

    void activatePlayers();
    bool arePlayersActive() const;

    void performBlind() const;

    void returnCardsFromPlayers() const;
    void returnCardsFromTable() const;

    void prepareCardsForVerdict() const;
    void setBestCombinations() const;
    void sortPlayersByHand();

    bool isTieAmongWinners();
    void payOutForWinners();

    void printPlayers() const;
    void printWinner();
    void displayHandsAndTable() const;

    std::shared_ptr<Verifier> verifier_;
    std::unique_ptr<Comparator> comparator_;
    std::shared_ptr<Deck> deck_;
    std::shared_ptr<Table> table_;
    std::vector<std::shared_ptr<Player>> players_;

    size_t roundNumber_ = 0;
    const size_t valueOfBlind_ = 100;
    const size_t maxNumberOfPlayers_ = 8;
    size_t numberOfActivePlayers_ = 0;
};

#endif