#pragma once
#include "deck.h"
#include "card.h"
#include <vector>

struct GameSystem;

class Player : public Effectable {
public:
	Player();
	Player(bool isAI, GameSystem& system);
	~Player();

	void drawCard();
	void fillHand();
	void removeHandCard(Card card);

	int getPlayerNumber();
	int getHealth();
	int getCurrentEnergy();
	void setCurrentEnergy(int value);
	Deck getDeck();
	std::vector<Card> getHand();

	void populateDeck();
	
	bool reduceHealth(int value) override;
	void increaseHealth(int value) override;
	bool applyEffect(Effect effect) override;

	__event void PlayerKilled(int playerNumber);

private:
	bool _isAI;
	int _playerNumber;
	int _currentEnergy;
	
	GameSystem& _system;
	Deck _deck;
	
	std::vector<Card> _hand;
};