#include "game_system.h"
#include "player.h"
#include "game_parameters.h"

#include <iostream>
#include <memory>

GameSystem::GameSystem() = default;
GameSystem::~GameSystem() = default;

void GameSystem::init() {
	GameSystem::createPlayers(false);
	_maxEnergy = GameParameters::startingEnergy;
}

void GameSystem::hookPlayerKilled(Player* player) {
	__hook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

void GameSystem::unhookPlayerKilled(Player* player) {
	__unhook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

void GameSystem::playerKilledHandler(int playerNumber) {
	std::cout << playerNumber << " died" << std::endl;
}

int GameSystem::getNextPlayerNumber() {
	GameSystem::_playerNumber++;
	return GameSystem::_playerNumber;
}

Player* GameSystem::getPlayer1() {
	return _player1.get();
}

Player* GameSystem::getPlayer2() {
	return _player2.get();
}

int GameSystem::getMaxEnergy() {
	return _maxEnergy;
}

void GameSystem::createPlayers(bool isP2Ai) {
	_player1 = std::make_unique<Player>(false, *this);
	_player2 = std::make_unique<Player>(false, *this);
}

int GameSystem::_playerNumber = 0;
int GameSystem::_maxEnergy = GameParameters::startingEnergy;