#include "game_system.h"
#include "player.h"
#include "game_parameters.h"

#include <iostream>
#include <memory>

//________________________________//
//          CONSTRUCTORS          //
//________________________________//
GameSystem::GameSystem() = default;
GameSystem::~GameSystem() = default;

//_______________________________//
//          EVENT HOOKS          //
//_______________________________//
// Event hook. Listens to "PlayerKilled" and runs "playerKilledHandler" when the event is invoked.
void GameSystem::hookPlayerKilled(Player* player) {
	__hook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

// Event unhook. Stops listening to "PlayerKilled".
void GameSystem::unhookPlayerKilled(Player* player) {
	__unhook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

//___________________________//
//          METHODS          //
//___________________________//
// Runs on game initialisation
void GameSystem::init() {
	GameSystem::createPlayers(false);
	_maxEnergy = GameParameters::startingEnergy;
}

// Instantiates player1 & player2
void GameSystem::createPlayers(bool isP2Ai) {
	_player1 = std::make_unique<Player>(false, *this);
	_player2 = std::make_unique<Player>(false, *this);
}

// Code that is run when event is invoked.
void GameSystem::playerKilledHandler(int playerNumber) {
	std::cout << playerNumber << " died" << std::endl;
}

//____________________________//
//          GETTTERS          //
//____________________________//
// Returns the next player number
int GameSystem::getNextPlayerNumber() {
	GameSystem::_playerNumber++;
	return GameSystem::_playerNumber;
}

// Returns a pointer to player1
Player* GameSystem::getPlayer1() {
	return _player1.get();
}

// Returns a pointer to player2
Player* GameSystem::getPlayer2() {
	return _player2.get();
}

// Gets the current max energy
int GameSystem::getMaxEnergy() {
	return _maxEnergy;
}

void GameSystem::setMaxEnergy(int value)
{
	_maxEnergy = value;
}

//___________________________________//
//          LOCAL VARIABLES          //
//___________________________________//
int GameSystem::_playerNumber = 0;
int GameSystem::_maxEnergy = GameParameters::startingEnergy;