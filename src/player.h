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
	// Add card to players graveyard
	void addToGraveyard(Card card);
	void fillHand();
	void removeHandCard(Card card);
	// Remove a revived card
	void removeGraveyardCard(Card card);

	void turnHandAcesInto11Aces();
	void turnDeckAcesInto11Aces();

	bool halfHandEnergyCost();
	bool doubleHandEnergyCost();

	int getPlayerNumber();
	int getHealth();
	int getCurrentEnergy();
	void setCurrentEnergy(int value);
	Deck& getDeck();
	std::vector<Card> getHand();
	std::vector<Card> getGraveyard();

	void forceCardIntoHand(Card &card);

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
	std::vector<Card> _graveyard;
};