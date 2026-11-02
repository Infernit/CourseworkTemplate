#include "game_system.h"
#include <iostream>

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

int GameSystem::_playerNumber = 0;