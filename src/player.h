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

	void drawCard();

	int getPlayerNumber();
	int getHealth();
	Deck getDeck();
	std::vector<Card> getHand();

	void populateDeck();
	
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