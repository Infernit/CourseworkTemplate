#pragma once
#include "card.h"
#include "game_parameters.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Board {

public:
	Board();
	void init();
	static const int tileWidth;
	static const int tileHeight;
	static unsigned int windowWidth;
	static unsigned int windowHeight;
	static std::vector<sf::Sprite> cards;
	sf::Vector2f gridToPixels(int gridX, int gridY);
	// in cpp: std::vector<sf::Sprite> cards;

	bool playCard(Player* player, Player* opponent, Card& card);
	std::vector<Card>& getEnemyCards(Player* player);
	std::vector<Card>& getFriendlyCards(Player* player);
	bool getIsEnemyAttackable(Player* player);

	void removeDeadCards();

	bool tryPlayCardToEffectable(Player* player, Player* opponent, Card& card);

	void setPlayerCardsUsable(Player* player);

	sf::Sprite cutCard(Card card);

	std::vector<Card>& getPlayer1BoardCards();
	std::vector<Card>& getPlayer2BoardCards();

	void placeCardsOnBoard(Player* p1, Player* p2, sf::RenderWindow& window);

private:
	std::vector<Card> _player1BoardCards;
	std::vector<Card> _player2BoardCards;
};