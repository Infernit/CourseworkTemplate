#pragma once
#include <vector>
#include "card.h"
#include "player.h"

class BoardFunctionality {
public:
	BoardFunctionality();

	bool playCard(Player* player, Card card);
	std::vector<Card> getEnemyCards(Player* player);
	bool getIsEnemyAttackable(Player* player);

	std::vector<Card> getPlayer1BoardCards();
	std::vector<Card> getPlayer2BoardCards();

private:
	std::vector<Card> _player1BoardCards;
	std::vector<Card> _player2BoardCards;
};