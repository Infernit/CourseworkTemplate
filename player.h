#pragma once
#include "deck.h"
#include "card.h"
#include <vector>

struct GameSystem;

class Player {
public:
	Player();
	Player(bool isAI, GameSystem& system);
	~Player();

	int getPlayerNumber();
	int getHealth();
	void populateDeck();
	Deck getDeck();
	void reduceHealth(int value);

	__event void PlayerKilled(int playerNumber);

private:
	bool _isAI;
	int _playerNumber;
	int _health;
	
	GameSystem& _system;
	Deck _deck;
	
	std::vector<Card> _hand;
};