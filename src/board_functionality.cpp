#include "board_functionality.h"
#include "game_parameters.h"
#include "player.h"
#include "board.h"

using params = GameParameters;

BoardFunctionality::BoardFunctionality() {
	_player1BoardCards = {};
	_player2BoardCards = {};
}

bool BoardFunctionality::playCard(Player* player, Player* opponent, Card& card) {
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
			card.setIsUsable(false);
			cards->push_back(card);
			player->removeHandCard(card);
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardRank());
			return true;
		}
	}
	else {
		if (tryPlayCardToEffectable(player, opponent, card)) {
			player->removeHandCard(card);
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardRank());
			return true;
		}
	}

	return false;
}

std::vector<Card>& BoardFunctionality::getEnemyCards(Player* player) {
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player2BoardCards;
	}
	else {
		return _player1BoardCards;
	}
}

std::vector<Card>& BoardFunctionality::getFriendlyCards(Player* player) {
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player1BoardCards;
	}
	else {
		return _player2BoardCards;
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

void BoardFunctionality::removeDeadCards() {
	int j = 0;

	for (int i = 0; i < _player1BoardCards.size(); i++) {
		if (_player1BoardCards[i].getIsDead()) {
			_player1BoardCards.erase(_player1BoardCards.begin() + i - j);
			j++;
		}
	}

	j = 0;

	for (int i = 0; i < _player2BoardCards.size(); i++) {
		if (_player2BoardCards[i].getIsDead()) {
			_player2BoardCards.erase(_player2BoardCards.begin() + i - j);
			j++;
		}
	}
}

bool BoardFunctionality::tryPlayCardToEffectable(Player* player, Player* opponent, Card& card) {
	std::vector<Card>* cardsToApplyTo;
	Player* playerToApplyTo;
	int index = 1;

	//Apply card to enemy
	if (card.getCardSuit().getSuitName() == clubs || card.getCardSuit().getSuitName() == spades) {
		cardsToApplyTo = &getEnemyCards(player);
		playerToApplyTo = opponent;
	}
	else {
		cardsToApplyTo = &getFriendlyCards(player);
		playerToApplyTo = player;
	}

	bool canHaveZeroElements = false;

	if (getIsEnemyAttackable(player) && card.getCardSuit().getSuitName() == clubs) {
		std::cout
			<< "0: Opposing Player"
			<< std::endl;
		canHaveZeroElements = true;
	}
	else if (card.getCardSuit().getSuitName() == hearts) {
		std::cout
			<< "0: Yourself"
			<< std::endl;
		canHaveZeroElements = true;
	}
		
	if (cardsToApplyTo->size() == 0 && !canHaveZeroElements) {
		return false;
	}

	
	for (Card card : *cardsToApplyTo) {
		std::cout
			<< index
			<< ": "
			<< params::cardNames[card.getCardRank()]
			<< " of "
			<< params::suitNames[card.getCardSuit().getSuitName()]
			<< std::endl;
		index++;
	}

	std::cout << "Pick card to effect: ";
	int num;
	std::cin >> num;

	//Apply card to target card
	if (num <= cardsToApplyTo->size() && num > 0) {
		return card.applyCardEffect(&(*cardsToApplyTo)[num - 1]);
	}
	else {
		return card.applyCardEffect(playerToApplyTo);
	}
}

void BoardFunctionality::setPlayerCardsUsable(Player* player) {
	std::vector<Card>* cards;

	if (player->getPlayerNumber() == 1) {
		cards = &_player1BoardCards;
	}
	else {
		cards = &_player2BoardCards;
	}

	for (int i = 0; i < cards->size(); i++) {
		cards->at(i).setIsUsable(true);
	}
}

sf::Sprite BoardFunctionality::cutCard(Card card) {
	sf::Sprite cardSprite(GameParameters::spritesheet);

	cardSprite.setTextureRect(
		sf::IntRect(
			sf::Vector2i(
				(card.getCardRank() - 1) * GameParameters::tileWidth,
				(card.getCardSuit().getSuitName() - 1) * GameParameters::tileHeight),
			sf::Vector2i(
				GameParameters::tileWidth,
				GameParameters::tileHeight)));

	return cardSprite;
}

std::vector<Card>& BoardFunctionality::getPlayer1BoardCards() {
	return _player1BoardCards;
}

std::vector<Card>& BoardFunctionality::getPlayer2BoardCards() {
	return _player2BoardCards;
}