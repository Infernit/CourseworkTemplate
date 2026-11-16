#pragma once
#include <vector>
#include "card.h"
#include "player.h"

class BoardFunctionality {
public:
	BoardFunctionality();

	bool playCard(Player* player, Player* opponent, Card& card);
	std::vector<Card>& getEnemyCards(Player* player);
	std::vector<Card>& getFriendlyCards(Player* player);
	bool getIsEnemyAttackable(Player* player);

	void hookCardKilled(Card* card);
	void unhookCardKilled(Card* card);
	void cardKilledHandler(Card* card);

	bool tryPlayCardToEffectable(Player* player, Player* opponent, Card& card);

	void setPlayerCardsUsable(Player* player);

	std::vector<Card>& getPlayer1BoardCards();
	std::vector<Card>& getPlayer2BoardCards();

private:
	std::vector<Card> _player1BoardCards;
	std::vector<Card> _player2BoardCards;
};