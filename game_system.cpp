#include "game_system.h"

void GameSystem::hookPlayerKilled(Player* player) {
	__hook(&Player::PlayerKilled, player, GameSystem::playerKilledHandler);
}

void GameSystem::unhookPlayerKilled(Player* player) {
	__unhook(&Player::PlayerKilled, player, GameSystem::playerKilledHandler);
}

void GameSystem::playerKilledHandler(int playerNumber) {
	std::cout << playerNumber << " died" << std::endl;
}