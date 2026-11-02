#pragma once
#include "game_parameters.h"
#include <iostream>

struct GameSystem {
	GameSystem();
	static void init();
	static void reset();
	static void clean();
	static void update(const float& dt);
	static void render();
	static int getNextPlayerNumber();

	void hookPlayerKilled(Player* player);
	void unhookPlayerKilled(Player* player);
	void playerKilledHandler(int playerNumber);
	static void createPlayers(bool isP2Ai, GameSystem system);

private:
	static Player _player1;
	static Player _player2;
	static int _playerNumber;
};