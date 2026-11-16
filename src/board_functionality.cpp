#include "board_functionality.h"
#include "game_parameters.h"
#include "player.h"

using params = GameParameters;

BoardFunctionality::BoardFunctionality() {
	_player1BoardCards = {};
	_player2BoardCards = {};
}

bool BoardFunctionality::playCard(Player* player, Card card) {
	if (player->getCurrentEnergy() < card.getCardRank()) {
		return false;
	}

	if (card.getCardSuit().getSuitName() == clubs || card.getCardSuit().getSuitName() == hearts) {
		std::vector<Card>* cards;

		//Determine which board to add the card to
		if (player->getPlayerNumber() == 1) {
			cards = &_player1BoardCards;
		}
		else {
			cards = &_player2BoardCards;
		}

		//Check if board size is less than limit
		if (cards->size() < params::boardSize) {
			cards->push_back(card);
			player->removeHandCard(card);
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardRank());
			return true;
		}
	}
	else {
		//go straight to card targeting
		//for now just dont allow it, so return false
	}

	return false;
}

std::vector<Card> BoardFunctionality::getEnemyCards(Player* player) {
	if (player->getPlayerNumber() == 1) {
		return _player2BoardCards;
	}
	else {
		return _player1BoardCards;
	}
}

bool BoardFunctionality::getIsEnemyAttackable(Player* player) {
	bool attackable = true;

	if (player->getPlayerNumber() == 1) {
		for (Card card : _player2BoardCards) {
			if (card.getCardSuit().getSuitName() == clubs) {
				attackable = false;
			}
		}
	}
	else {
		for (Card card : _player1BoardCards) {
			if (card.getCardSuit().getSuitName() == clubs) {
				attackable = false;
			}
		}
	}

	return attackable;
}

std::vector<Card> BoardFunctionality::getPlayer1BoardCards() {
	return _player1BoardCards;
}

std::vector<Card> BoardFunctionality::getPlayer2BoardCards() {
	return _player2BoardCards;
}