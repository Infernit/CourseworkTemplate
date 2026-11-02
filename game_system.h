#pragma once
#include "game_parameters.h"
#include "player.h"

struct GameSystem {
	static void init();
	static void reset();
	static void clean();
	static void update(const float& dt);
	static void render();
	static int getNextPlayerNumber();

	void hookPlayerKilled(Player* player);
	void unhookPlayerKilled(Player* player);
	void playerKilledHandler(int playerNumber);

private:
	static int _playerNumber;
};