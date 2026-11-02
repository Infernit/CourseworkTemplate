#pragma once
#include <iostream>
#include <memory>

class Player;

struct GameSystem {
	GameSystem();
	~GameSystem();

	void init();
	void reset();
	void clean();
	void update(const float& dt);
	void render();

	int getNextPlayerNumber();

	void hookPlayerKilled(Player* player);
	void unhookPlayerKilled(Player* player);

	void playerKilledHandler(int playerNumber);

	void createPlayers(bool isP2Ai);

	Player* getPlayer1();

	Player* getPlayer2();


private:
	std::unique_ptr<Player> _player1;
	std::unique_ptr<Player> _player2;
	static int _playerNumber;
};