#include "game_system.h"
#include <iostream>

GameSystem::GameSystem() {

}

void GameSystem::init() {
	GameSystem system;
	GameSystem::createPlayers(false, system);
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

void GameSystem::createPlayers(bool isP2Ai, GameSystem system) {
	Player p1(false, system);
	GameSystem::_player1 = p1;
	Player p2(isP2Ai, system);
	GameSystem::_player2 = p2;
}

Player GameSystem::_player1;
Player GameSystem::_player2;

int GameSystem::_playerNumber = 0;