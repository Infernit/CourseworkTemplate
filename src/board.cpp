#include "board.h"
#include <SFML/Graphics.hpp>
#include <iostream>

sf::Vector2f Board::pixelsToGrid(sf::Vector2f mousePos) {
	int gridX = static_cast<int>(mousePos.x) / GameParameters::tileWidth;
	int gridY = static_cast<int>(mousePos.y) / GameParameters::tileHeight;
	return sf::Vector2f(gridX, gridY);
}

sf::Vector2f Board::gridToPixels(int gridX, int gridY) {
	return sf::Vector2f(gridX * GameParameters::tileWidth, gridY * GameParameters::tileHeight);
}

// Prepare for interactive draggable cards
sf::Vector2f Board::getCardPosition(sf::Sprite cardSprite) {
	// SFML sprites inherit from Transformable, so get position
	return Board::pixelsToGrid(cardSprite.getPosition());
}

// yValue = 2 (player 1) or 3 (player 2)
// x ranges 4 - 8
void Board::makeValidPlayTilesGlowGreen(int yValue) {
	// Valid x for tiles
	std::vector<int> xRanges = { 4, 5, 6, 7, 8 };

	for (Tile tile : boardTiles) {
		for (int x : xRanges) {
			if (tile.getX() == x && tile.getY() == yValue) {
				// Change colour ???

			}
		}
	}

}

Board::Board(GameSystem* system)  {
	_system = system;

	//Set both player's cards to empty.
    _player1BoardCards = {};
    _player2BoardCards = {};
	// Set graveyard cards
	_player1GraveyardCards = {};
	_player2GraveyardCards = {};

	_playerHandTiles[1] = {};
	_playerHandTiles[2] = {};
	_playerBoardTiles[1] = {};
	_playerBoardTiles[2] = {};
	_playerGraveyardTiles[1] = {};
	_playerGraveyardTiles[2] = {};
	
	//Attempt to load spritesheet and throw error if fails.
	std::string sprite_path = std::string(RESOURCE_DIR) + "/img/sprite_sheet.png";
	std::cout << "Loading spritesheet from: " << sprite_path << std::endl;

	if (!GameParameters::spritesheet.loadFromFile(sprite_path)) {
		std::cerr << "Failed to load spritesheet!" << std::endl;
	}

	//Attempt to load font and throw error if fails.
	std::string font_path = std::string(RESOURCE_DIR) + "/txt/PublicPixel.otf";
	std::cout << "Loading font from: " << font_path << std::endl;

	if (!GameParameters::font.loadFromFile(font_path)) {
		std::cerr << "Failed to load font!" << std::endl;
	}

	//Cut cardDescBar from spritesheet
	sf::Sprite temp(GameParameters::spritesheet);
	temp.setTextureRect(
		sf::IntRect(
			sf::Vector2i(429, 90),
			sf::Vector2i(16, 45)));
	GameParameters::cardDescBar = temp;

	temp.setTextureRect(
		sf::IntRect(
			sf::Vector2i(429, 135),
			sf::Vector2i(16, 45)));
	GameParameters::cardEnergyBar = temp;

	//Cut club icon from spritesheet
	temp.setTextureRect(sf::IntRect(
		sf::Vector2i(445, 90),
		sf::Vector2i(4, 4)));
	GameParameters::club = temp;

	//Cut heart icon from spritesheet
	temp.setTextureRect(sf::IntRect(
		sf::Vector2i(445, 94),
		sf::Vector2i(4, 4)));
	GameParameters::heart = temp;

}

void Board::removeDeadCards() {
	int j = 0;
	int size = _player1BoardCards.size();

	//Loop through all player 1 cards
	for (int i = 0; i < size; i++) {
		if (_player1BoardCards[i - j].getIsDead()) {
			if (_player1BoardCards[i - j].getCaptured()) {
				_player2CapturedCard.setCardRank(0);
				_player1BoardCards[i - j].setCaptured(false);
			}
			if (_player1CapturedCard.getCardRank() != 0 &&
				_player1BoardCards[i - j].getCardRank() == 1 &&
				_player1BoardCards[i - j].getCardSuit().getSuitName() == clubs) {
				_player1CapturedCard.setCardRank(0);
				
				for (int k = 0; k < _player2BoardCards.size(); k++) {
					if (_player2BoardCards[k].getCaptured()) {
						_player2BoardCards[k].setCaptured(false);
						break;
					}
				}
			}
			// Add to the graveyard
			_player1GraveyardCards.push_back(_player1BoardCards[i - j]);
			//If card is dead erase it from the list.
			_player1BoardCards.erase(_player1BoardCards.begin() + i - j);
			//Increment removed cards.
			j++;
		}
	}

	j = 0;
	size = _player2BoardCards.size();

	//Loop through all player 2 cards
	for (int i = 0; i < size; i++) {
		if (_player2BoardCards[i - j].getIsDead()) {
			if (_player2BoardCards[i - j].getCaptured()) {
				_player1CapturedCard.setCardRank(0);
				_player2BoardCards[i - j].setCaptured(false);
			}
			if (_player2CapturedCard.getCardRank() != 0 &&
				_player2BoardCards[i - j].getCardRank() == 1 &&
				_player2BoardCards[i - j].getCardSuit().getSuitName() == clubs) {
				_player2CapturedCard.setCardRank(0);

				for (int k = 0; k < _player1BoardCards.size(); k++) {
					if (_player1BoardCards[k].getCaptured()) {
						_player1BoardCards[k].setCaptured(false);
						break;
					}
				}
			}
			// Add to the graveyard
			_player2GraveyardCards.push_back(_player2BoardCards[i - j]);
			//If card is dead erase it from the list.
			_player2BoardCards.erase(_player2BoardCards.begin() + i - j);
			//Increment removed cards.
			j++;
		}
	}
}

bool Board::playCard(Player* player, Player* opponent, Card& card) {
	//Don't let the card be played if the player doesn't have enough energy.
	if (player->getCurrentEnergy() < card.getCardEnergyCost()) {
		return false;
	}

	//Cards that are played to the board before being used.
	if (card.getCardSuit().getSuitName() == clubs || card.getCardSuit().getSuitName() == hearts) {
		std::vector<Card>* cards;

		//Determine which board to add the card to.
		if (player->getPlayerNumber() == 1) {
			cards = &_player1BoardCards;
		}
		else {
			cards = &_player2BoardCards;
		}

		//Check if board size is less than limit.
		if (cards->size() < GameParameters::boardSize) {
			//Card shouldn't be usable until next turn.
			card.setIsUsable(false);
			//Add card to board.
			cards->push_back(card);
			//Remove card from hand.
			player->removeHandCard(card);
			//Reduce player energy by card cost.
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardEnergyCost());
			//Card played successfully.
			return true;
		}
	}

	// Cards that are played straight from the hand.
	else {
		// Try to play the card.
		if (playCardRankAndSuit(player, opponent, card)) {
			//If succeeds remove card from hand and reduce player energy by card cost.
			player->removeHandCard(card);
			// Then add to graveyard
			player->addToGraveyard(card);
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardEnergyCost());
			// Card played successfully.
			return true;
		}
	}

	// Otherwise card was not played.
	return false;
}

std::vector<Card>& Board::getEnemyCards(Player* player) {
	//Make sure all dead cards are removed before getting cards.
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player2BoardCards;
	}
	else {
		return _player1BoardCards;
	}
}

bool Board::effectEnemyKingOfHearts(Player* player, Effect effect) {
	//Make sure all dead cards are removed before getting cards.
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		for (int i = 0; i < _player2BoardCards.size(); i++) {
			if (_player2BoardCards[i].getCardRank() == 13 && _player2BoardCards[i].getCardSuit().getSuitName() == hearts) {
				return effect.applyEffect(&_player2BoardCards[i]);
			}
		}
	}
	else {
		for (int i = 0; i < _player1BoardCards.size(); i++) {
			if (_player1BoardCards[i].getCardRank() == 13 && _player1BoardCards[i].getCardSuit().getSuitName() == hearts) {
				return effect.applyEffect(&_player1BoardCards[i]);
			}
		}
	}

	return false;
}

std::vector<Card>& Board::getFriendlyCards(Player* player) {
	//Make sure all dead cards are removed before getting cards.
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player1BoardCards;
	}
	else {
		return _player2BoardCards;
	}
}

std::vector<Card>& Board::getFriendlyGraveyardCards(Player* player) {
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player1GraveyardCards;
	}
	else {
		return _player2GraveyardCards;
	}
}

bool Board::getIsEnemyAttackable(Player* player) {
	//Set flag to true by default.
	bool attackable = true;

	if (player->getPlayerNumber() == 1) {
		for (Card card : _player2BoardCards) {
			if (card.getCardSuit().getSuitName() == clubs) {
				//If found a club, set flag to false.
				attackable = false;
				//End loop.
				break;
			}
		}
	}
	else {
		for (Card card : _player1BoardCards) {
			if (card.getCardSuit().getSuitName() == clubs) {
				//If found a club, set flag to false.
				attackable = false;
				//End loop.
				break;
			}
		}
	}

	//Return flag.
	return attackable;
}

bool Board::playCardRankAndSuit(Player* player, Player* opponent, Card& card) {
	switch (card.getCardRank()) {
		// Ace
		case 1:
			// Check turn-number/current energy
			// Special if 11 ace
			if (GameSystem::getMaxEnergy() >= 11) {

				Effect effect;

				switch (card.getCardSuit().getSuitName()) {
				case hearts:
					// effect handled elsewhere
					//tryPlayCardToEffectable(player, opponent, card);
					// 11 Ace - Heal all friendly minions by 5 every turn while on the board.
					card.setIsUsable(false);
					return aceHeartsEffectable(player);
					break;
				case clubs:
					/*
					11 Ace - Captures an enemy minion. The captured cannot do any action, and takes 11 damage every turn until they die. 
					Can only be freed by cleanse or capturing/killing. Once the captured card dies, the ace can capture another card. 
					The captured does not start taking damage until the turn after the capture.
					*/
					//tryPlayCardToEffectable(player, opponent, card);
					if (!aceHasCapturedCard(player)) {
						card.setIsUsable(false);
						return tryPlayCardToEffectable(player, opponent, card);
					}
					break;
				case spades:
					// 11 Ace - Instakills anything it is applied to.
					effect = Effect(false, damage, 2000.f);
					card.setEffect(effect);
					return tryPlayCardToEffectable(player, opponent, card);
					break;
				case diamonds:
					// 11 Ace - Fully restore energy plus gain an extra 11.
					player->setCurrentEnergy(GameSystem::getMaxEnergy() + 11);
					return true;
					break;
				default:
					break;
				}

			}
			
			else {
				return tryPlayCardToEffectable(player, opponent, card);
			}

			break;
		// Jack
		case 11:
			switch (card.getCardSuit().getSuitName()) {
				case hearts:
					// effect handled elsewhere
					tryPlayCardToEffectable(player, opponent, card);
					break;
				case clubs:
					// damage between 5 and 20
					tryPlayCardToEffectable(player, opponent, card);
					card.generateJackDamage();
					break;
				case spades:
					// Jack - Doubles mana cost of all cards in the opponent’s hand (to a cap of their max mana).
					return jackSpadeEffectable(opponent);
					break;
				case diamonds:
					return jackDiamondEffectable(player);
					break;
				default:
					break;
				}

			break;

		// Queen
		case 12:

			switch (card.getCardSuit().getSuitName()) {
				case hearts:
					// Graveyard
					// Bring back the next numbered card from the graveyard once every 3 turns 
					if (queenHeartsEffectable(player)) {
						card.setIsUsable(false);
						return true;
					}

					else {
						std::cout << "\nERROR: No card in graveyard.\n\n";
						return false;
					}

					break;
					// hearts elsewhere
				case clubs:
					// Damage dealt is spread evenly across all enemy minions.
					if (queenClubsEffectable(player)) {
						card.setIsUsable(false);
						return true;
					}
					break;
				case spades:
					// Halves all enemy damage dealt for 2 turns.
					return queenSpadeEffectable(player);
					break;
				case diamonds:
					// Bring back one non-ace from graveyard (then Queen disappears).
					if (queenDiamondEffectable(player)) {
						return true;
					}
					else {
						std::cout << "\nERROR: No card in graveyard.\n\n";
						return false;
					}
					break;
				default:
					break;
			}

			break;

		// King
		case 13:

			// Suits
			switch (card.getCardSuit().getSuitName()) {
				// Cannot heal or be healed. All damage dealt to any friendly card is dealt to this card instead. Has 100 health.
				case hearts:
					// When an attack is made, just check if its on the board
					//kingHeartsEffectable(player);
					card.setIsUsable(false);
					break;
				case clubs:
					// King - Has 40 health instead of 20. Deals 5 damage instead of 10.
					// Should be in card / hardcoded
					return tryPlayCardToEffectable(player, opponent, card);
					break;
				case spades:
					// King - Skips the opponent’s next turn.
					// NON FUNCTIONAL
					return kingSpadeEffectable(player);
					break;
				case diamonds:
					// King - Rally effect. Grant all cards on board 10 overhealth.
					if (kingDiamondEffectable(player)) {
						return true;
					}
					else {
						std::cout << "\nERROR: No cards to apply overhealth.\n\n";
						return false;
					}
					break;
				default:
					break;
			}

			break;

			//IF NORMAL CARD
		default:
			return tryPlayCardToEffectable(player, opponent, card);
			break;
		}

	return false;
}

bool Board::tryPlayCardToEffectable(Player* player, Player* opponent, Card& card) {
	
	std::vector<Card>* cardsToApplyTo;
	Player* playerToApplyTo;
	int index = 1;
	bool kingOfHeartsPresentOnEnemyBoard = false;

	// Apply card to enemy.
	if (card.getCardSuit().getSuitName() == clubs || card.getCardSuit().getSuitName() == spades) {

		kingOfHeartsPresentOnEnemyBoard = isKingOfHeartsOnBoard(opponent);

		if (kingOfHeartsPresentOnEnemyBoard) {
			if (card.getCardRank() == 1 && card.getCardSuit().getSuitName() == clubs && GameSystem::getMaxEnergy() >= 11) {
				aceCaptureCard(player, getEnemyKingOfHearts(opponent));
			}
			else if (effectEnemyKingOfHearts(player, card.getCardEffect())) {
			}
			else {
				return false;
			}

			card.setIsUsable(false);
			return true;
		}

		else {
			cardsToApplyTo = &getEnemyCards(player);
		}

		playerToApplyTo = opponent;
	}

	// Apply card to ally.
	else {
		cardsToApplyTo = &getFriendlyCards(player);
		playerToApplyTo = player;
	}

	//Flag lowered by default.
	bool canHaveZeroElements = false;

	//If opponent is attackable, and card is a club, opposing player is a target. Last bit is to prevent the ace of clubs trying to capture the player.
	if (getIsEnemyAttackable(player) && card.getCardSuit().getSuitName() == clubs && !kingOfHeartsPresentOnEnemyBoard && (card.getCardRank() != 1 && GameSystem::getMaxEnergy() < 11)) {
		std::cout
			<< "0: Opposing Player"
			<< std::endl;
		canHaveZeroElements = true;
	}
	//If card is a heart, current player is a target.
	else if (card.getCardSuit().getSuitName() == hearts && card.getCardRank() <= 10) {
		std::cout
			<< "0: Yourself"
			<< std::endl;
		canHaveZeroElements = true;
	}

	//No cards or players to apply to. Exit as failed to play.
	if (cardsToApplyTo->size() == 0 && !canHaveZeroElements) {
		return false;
	}

	//Prints out a list of cards that effect can be applied to.
	for (Card card1 : *cardsToApplyTo) {
		if (!(!card1.getIsHealable() && !card1.getCaptured() && card.getCardSuit().getSuitName() == hearts)) {
			std::cout
				<< index
				<< ": "
				<< GameParameters::cardNames[card1.getCardRank()]
				<< " of "
				<< GameParameters::suitNames[card1.getCardSuit().getSuitName()]
				<< std::endl;
			index++;
		}
	}

	//Allow player to choose card / player to apply effect to.
	std::cout << "Pick card to effect: ";
	int num;
	std::cin >> num;

	//Apply card to target card.
	if (num <= cardsToApplyTo->size() && num > 0) {
		if (card.getCardRank() == 1 && card.getCardSuit().getSuitName() == clubs && GameSystem::getMaxEnergy() >= 11) {
			return aceCaptureCard(player, &(*cardsToApplyTo)[num - 1]);
		}

		//Attempt to apply effect.
		return card.applyCardEffect(&(*cardsToApplyTo)[num - 1]);
	}
	//If not one of the numbers just assume it's 0 (not really bothering with proper validation) and effect the player instead.
	else {
		//Attempt to apply effect.
		return card.applyCardEffect(playerToApplyTo);
	}
}

bool Board::jackSpadeEffectable(Player* opponent) {

	opponent->doubleHandEnergyCost();

	return true;
}

bool Board::jackDiamondEffectable(Player* player) {

	return player->halfHandEnergyCost();
}

void Board::resetDamageDebuffs(Player* player)
{
	std::vector<Card>* cardsToReset;

	if (player->getPlayerNumber() == 1) {
		cardsToReset = &_player1BoardCards;
	}
	else {
		cardsToReset = &_player2BoardCards;
	}

	for (int i = 0; i < cardsToReset->size(); i++) {
		cardsToReset->at(i).resetDamageDecrease();
	}
}

// Where to record the turn this starts on (so it can occur every 3 ...)?
bool Board::queenHeartsEffectable(Player* player) {

	return graveyardTemplate(player, 1);

	//return true;
	
}

// Avoid copy paste between heart and diamond
bool Board::graveyardTemplate(Player* player, int num) {

	//Allow player to choose card / player to apply effect to.
	bool validating = true;


	std::vector<Card>* cardsToApplyTo = &getFriendlyGraveyardCards(player);

	if (cardsToApplyTo->size() == 0) {
		return false;
	}

	// 1 for hearts, 2 for diamonds

	while (validating) {

		//Breaks out if no cards to revive
		if (cardsToApplyTo->size() == 0) {
			return true;
		}

		//Prints out a list of numebered cards that could be revived
		std::cout << "Select card to revive:\n";

		int limit = 1;

		for (int i = 0; i < cardsToApplyTo->size(); i++) {
			// numbered only
			if (num == 1) {
				if (cardsToApplyTo->at(i).getCardRank() < 11) {
					std::cout
						<< (i + 1)
						<< ": "
						<< GameParameters::cardNames[cardsToApplyTo->at(i).getCardRank()]
						<< " of "
						<< GameParameters::suitNames[cardsToApplyTo->at(i).getCardSuit().getSuitName()]
						<< std::endl;

					limit++;
				}
			}
			else if (num == 2) {
				if (cardsToApplyTo->at(i).getCardRank() != 1) {
					std::cout
						<< (i + 1)
						<< ": "
						<< GameParameters::cardNames[cardsToApplyTo->at(i).getCardRank()]
						<< " of "
						<< GameParameters::suitNames[cardsToApplyTo->at(i).getCardSuit().getSuitName()]
						<< std::endl;

					limit++;
				}
			}

		}

		int num1;
		std::cin >> num1;
		int index = 0;
		bool doCheck = false;

		//Within bounds of options
		if (num1 < limit && num1 > 0) {
			for (int i = 0; i < player->getDeck().getDrawnCards().size(); i++) {
				doCheck = false;

				if (num == 1 && cardsToApplyTo->at(num1 - 1).getCardRank() < 11) {
					doCheck = true;
				}

				else if (num == 2 && cardsToApplyTo->at(num1 - 1).getCardRank() != 1) {
					doCheck = true;
				}

				if (doCheck) {
					if (player->getDeck().getDrawnCards()[index].getCardRank() == cardsToApplyTo->at(num1 - 1).getCardRank()
						&& player->getDeck().getDrawnCards()[index].getCardSuit().getSuitName() == cardsToApplyTo->at(num1 - 1).getCardSuit().getSuitName()) {
						//Removes Card from drawn cards
						player->getDeck().eraseAt(index);

						//Removes card from graveyard cards.
						cardsToApplyTo->erase(cardsToApplyTo->begin() + num1 - 1);

						validating = false;
						break;
					}

					index++;
				}
			}
		}
	}

	return true;

}

bool Board::queenClubsEffectable(Player* player) {

	std::vector<Card>* cardsToApplyTo = &getEnemyCards(player);

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		// attack each card on the board by 10 / the number of cards on the board
		cardsToApplyTo->at(i).reduceHealth(10 / cardsToApplyTo->size());
	}

	return true;

}

// For two turns implementation ...
// Queen - Halves all enemy damage dealt for 2 turns.
bool Board::queenSpadeEffectable(Player* player) {

	std::vector<Card>* cardsToApplyTo = {};

	// potential issue / may require different function in card (?)
	if (player->getPlayerNumber() == 1) {
		cardsToApplyTo = &_player2BoardCards;
	}

	else {
		cardsToApplyTo = &_player1BoardCards;
	}

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		cardsToApplyTo->at(i).setDamageDecreasePercent(0.5f);
	}

	return true;

}

// Queen - Bring back one non-ace from graveyard (then Queen disappears).
bool Board::queenDiamondEffectable(Player* player) {

	return graveyardTemplate(player, 2);

	// Will it dissapear itself as property of being a diamond or will this manually have to be handled (ie code from effectable?)
}

// King - Rally effect. Grant all cards on board 10 overhealth.
bool Board::kingDiamondEffectable(Player* player) {

	std::vector<Card>* cardsToApplyTo = &getFriendlyCards(player);

	if (cardsToApplyTo->size() == 0) {
		return false;
	}

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		// Give 10 overhealth. Cannot be healed
		// In the situation that the king dies, and is revived whilst cards have overhealth ...
		// Just set back to 10
		cardsToApplyTo->at(i).setOverhealth(10);
	}
	return true;

}

// King - Skips the opponent’s next turn.
bool Board::kingSpadeEffectable(Player* player) {
	_system->setSkipTurn(true);
	return true;
}

bool Board::isKingOfHeartsOnBoard(Player* opponent) {
	// potential issue / may require different function in card (?)
	std::vector<Card>* cardsToApplyTo = &getFriendlyCards(opponent);

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		// Enum?
		if (cardsToApplyTo->at(i).getCardSuit().getSuitName() == hearts && cardsToApplyTo->at(i).getCardRank() == 13) {
			// Then apply the damage to the king of hearts instead. Return true
			if (cardsToApplyTo->at(i).getCaptured()) {
				return false;
			}
			return true;
		}
	}

	// Else, return false
	return false;
}

Card* Board::getEnemyKingOfHearts(Player* opponent)
{
	std::vector<Card>* cardsToApplyTo = &getFriendlyCards(opponent);

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		// Enum?
		if (cardsToApplyTo->at(i).getCardSuit().getSuitName() == hearts && cardsToApplyTo->at(i).getCardRank() == 13) {
			// Then apply the damage to the king of hearts instead. Return true
			return &cardsToApplyTo->at(i);
		}
	}

	return nullptr;
}

// 11 Ace - Heal all friendly minions by 5 every turn while on the board.
bool Board::aceHeartsEffectable(Player* player) {
	
	std::vector<Card>* cardsToApplyTo = &getFriendlyCards(player);

	// 11 Ace - Heal all friendly minions by 5 every turn while on the board.
	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		Effect heal = Effect(true, healing, 5);
		cardsToApplyTo->at(i).applyEffect(heal);
	}

	return true;

}

bool Board::aceHasCapturedCard(Player* player)
{
	if (player->getPlayerNumber() == 1) {
		return _player1CapturedCard.getCardRank() != 0;
	}
	else {
		return _player2CapturedCard.getCardRank() != 0;
	}
}

bool Board::aceCaptureCard(Player* player, Card* card)
{
	if (aceHasCapturedCard(player)) {
		return false;
	}

	if (player->getPlayerNumber() == 1 &&
		_player2CapturedCard.getCardRank() != 0 &&
		card->getCardRank() == 1 &&
		card->getCardSuit().getSuitName() == clubs) {

		std::vector<Card>* cards = &getFriendlyCards(player);

		for (int i = 0; i < cards->size(); i++) {
			if (cards->at(i).getCardRank() == _player2CapturedCard.getCardRank() &&
				cards->at(i).getCardSuit().getSuitName() == _player2CapturedCard.getCardSuit().getSuitName()) {
				cards->at(i).setCaptured(false);
			}
		}
		_player2CapturedCard.setCardRank(0);
	}
	else if (player->getPlayerNumber() == 2 &&
		_player1CapturedCard.getCardRank() != 0 &&
		card->getCardRank() == 1 &&
		card->getCardSuit().getSuitName() == clubs){

		std::vector<Card>* cards = &getFriendlyCards(player);

		for (int i = 0; i < cards->size(); i++) {
			if (cards->at(i).getCardRank() == _player1CapturedCard.getCardRank() &&
				cards->at(i).getCardSuit().getSuitName() == _player1CapturedCard.getCardSuit().getSuitName()) {
				cards->at(i).setCaptured(false);
			}
		}
		_player1CapturedCard.setCardRank(0);
	}

	card->setCaptured(true);

	if (player->getPlayerNumber() == 1) {
		_player1CapturedCard = *card;
	}
	else {
		_player2CapturedCard = *card;
	}

	return true;
}

bool Board::aceDamageCard(Player* player)
{
	Effect effect(false, damage, 11.f);

	std::vector<Card>* cards = &getEnemyCards(player);

	if (player->getPlayerNumber() == 1 && _player1CapturedCard.getCardRank() != 0) {
		for (int i = 0; i < cards->size(); i++) {
			if (cards->at(i).getCardRank() == _player1CapturedCard.getCardRank() &&
				cards->at(i).getCardSuit().getSuitName() == _player1CapturedCard.getCardSuit().getSuitName()) {
				cards->at(i).applyEffect(effect);
			}
		}
		
	}
	else if (player->getPlayerNumber() == 2 && _player2CapturedCard.getCardRank() != 0) {
		for (int i = 0; i < cards->size(); i++) {
			if (cards->at(i).getCardRank() == _player2CapturedCard.getCardRank() &&
				cards->at(i).getCardSuit().getSuitName() == _player2CapturedCard.getCardSuit().getSuitName()) {
				cards->at(i).applyEffect(effect);
			}
		}
	}
	else {
		return false;
	}

	removeDeadCards();

	return true;
}

void Board::setPlayerCardsUsable(Player* player) {
	std::vector<Card>* cards;

	if (player->getPlayerNumber() == 1) {
		cards = &_player1BoardCards;
	}
	else {
		cards = &_player2BoardCards;
	}

	//Loop through all of player's cards and set them as usable.
	for (int i = 0; i < cards->size(); i++) {
		if (!(cards->at(i).getCardRank() == 13 &&
			cards->at(i).getCardSuit().getSuitName() == hearts) &&
			!(cards->at(i).getCaptured()) &&
			!(cards->at(i).getCardRank() == 1 &&
				cards->at(i).getCardSuit().getSuitName() == clubs &&
				GameSystem::getMaxEnergy() >= 11 &&
				(player->getPlayerNumber() == 1 ? _player1CapturedCard : _player2CapturedCard).getCardRank() != 0)
			) {
			cards->at(i).setIsUsable(true);
		}
	}
}

sf::Sprite Board::cutCard(Card card) {
	sf::Sprite cardSprite(GameParameters::spritesheet);

	//Cut out card from spritesheet (should work for ranks ace - king).
	cardSprite.setTextureRect(
		sf::IntRect(
			sf::Vector2i(
				(card.getCardRank() - 1) * GameParameters::tileWidth,
				(card.getCardSuit().getSuitName() - 1) * GameParameters::tileHeight),
			sf::Vector2i(
				GameParameters::tileWidth,
				GameParameters::tileHeight)));

	//Return cut sprite.
	return cardSprite;
}

// Implement turn number tracker for Queen Spades and Queen Hearts
// AND king skipping (spades)

// Return the tile a card is on
//? Board::returnCardTile(Card card) {
//
//}

void Board::changeTileToOccupied(int xVal, int yVal) {
	/*
	for (x = 0; x < ((int)(GameParameters::windowWidth /
		(GameParameters::tileWidth + GameParameters::cardDescBarWidth))); x++) {
		for (int y = 0; y < GameParameters::windowHeight / GameParameters::tileHeight - 1; y++) {
			if (x == xVal && y = yVal) {

			}
		}
	}
	*/
	for (Tile tile : boardTiles) {
		if (tile.getX() == xVal && tile.getY() == yVal) {
			tile.setOccupied(true);
		}
	}
}

Tile Board::getTileFromBoardtiles(int xVal, int yVal) {
	for (Tile tile : boardTiles) {
		if (tile.getX() == xVal && tile.getY() == yVal) {
			return tile;
		}
	}
}

sf::Sprite Board::setPositionRelativeToCardDescBar(Tile tile, sf::Sprite sprite, int xOffset, int yOffset)
{
	sprite.setPosition((GameParameters::tileWidth + GameParameters::cardDescBarWidth) * tile.getX() + xOffset + GameParameters::tileWidth,
		GameParameters::tileHeight * tile.getY() + GameParameters::healthBarHeight + yOffset);
	return sprite;
}

sf::Text Board::setPositionRelativeToCardDescBar(Tile tile, sf::Text sprite, int xOffset, int yOffset) {
	sprite.setPosition((GameParameters::tileWidth + GameParameters::cardDescBarWidth) * tile.getX() + xOffset + GameParameters::tileWidth,
		GameParameters::tileHeight * tile.getY() + GameParameters::healthBarHeight + yOffset);
	return sprite;
}

void Board::placeCardsOnBoard(Player* p1, Player* p2, sf::RenderWindow& window) {

	//New system trial code
	// Player 2 healthbar space

	sf::RectangleShape healthbarPlayer2Red(sf::Vector2f((GameParameters::windowWidth), GameParameters::healthBarHeight));
	// make sure its being positioned correctly
	healthbarPlayer2Red.setPosition(0.f, 0.f);
	healthbarPlayer2Red.setFillColor(sf::Color::Red);
	window.draw(healthbarPlayer2Red);

	// Place a green on top that will decrease in size as player takes damage
	sf::RectangleShape healthbarPlayer2(sf::Vector2f((float)(GameParameters::windowWidth) * (float)p2->getHealth() / (float)GameParameters::maxPlayerHealth, GameParameters::healthBarHeight));
	healthbarPlayer2.setPosition(0.f, 0.f);
	healthbarPlayer2.setFillColor(sf::Color::Green);
	window.draw(healthbarPlayer2);

	//Player 1 healthbar
	sf::RectangleShape healthbarPlayer1Red(sf::Vector2f((GameParameters::windowWidth), GameParameters::healthBarHeight));
	// make sure its being positioned correctly
	healthbarPlayer1Red.setPosition(0.f, (GameParameters::tileHeight * 6) + GameParameters::healthBarHeight);
	healthbarPlayer1Red.setFillColor(sf::Color::Red);
	window.draw(healthbarPlayer1Red);

	// Place a green on top that will decrease in size as player takes damage
	sf::RectangleShape healthbarPlayer1(sf::Vector2f((float)(GameParameters::windowWidth) * (float)p1->getHealth() / (float)GameParameters::maxPlayerHealth, GameParameters::healthBarHeight));
	// To account for lines (1px each)
	healthbarPlayer1.setPosition(0.f, (GameParameters::tileHeight * 6) + GameParameters::healthBarHeight);
	healthbarPlayer1.setFillColor(sf::Color::Green);
	window.draw(healthbarPlayer1);

	Player* p;
	std::vector<int> limits = { 
		GameParameters::handSize, 
		GameParameters::boardSize, 
		8
	};
	std::vector<std::map<int, std::vector<Tile>>*> maps = { 
		&_playerHandTiles, 
		&_playerBoardTiles, 
		&_playerGraveyardTiles 
	};

	for (int i = 0; i < 2; i++) {
		if (i == 0) {
			p = p1;
		}
		else {
			p = p2;
		}

		std::vector<std::vector<Card>> currentCards = {
			p->getHand(),
			getFriendlyCards(p),
			getFriendlyGraveyardCards(p)
		};

		std::vector<int> xPositions = {
			0,
			1,
			8
		};

		std::vector<int> yPositions = {
			(p->getPlayerNumber() == 1 ? 5 : 0),
			(p->getPlayerNumber() == 1 ? 3 : 2),
			(p->getPlayerNumber() == 1 ? 3 : 2)
		};

		//loop through hand, then board, then graveyard
		for (int k = 0; k < limits.size(); k++) {
			for (int j = 0; j < limits[k]; j++) {
				//always create a tile even if there isnt a card in it
				Tile tile(j + xPositions[k], yPositions[k], true, GameParameters::tileWidth, GameParameters::tileHeight, sf::Color::Yellow);

				sf::Sprite s;
				sf::Text txt;
				txt.setFont(GameParameters::font);
				txt.setCharacterSize(4);

				//cut card if exists
				//only do this if there is a card in that hand slot
				if (j < currentCards[k].size()) {
					//cut card
					s = cutCard(currentCards[k][j]);
					tile.setOccupied(true);
					tile.resetCardDescBarSprites();

					if (k == 0) {
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, GameParameters::cardEnergyBar, 0, 0));
						txt.setString(std::to_string(currentCards[k][j].getCardEnergyCost()));
						txt.setColor(sf::Color(0, 0, 0, 255));
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, txt, 9, 20));
					}

					else if (k == 1) {
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, GameParameters::cardDescBar, 0, 0));

						if (currentCards[k][j].getCardSuit().getSuitName() == clubs) {
							//If the card is a club, draw the club icon in the first slot.
							tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, GameParameters::club, 3, 7));

							//Set the colour of the text next to it to the club colour.
							txt.setColor(sf::Color(91, 110, 225, 255));
						}

						else if (currentCards[k][j].getCardSuit().getSuitName() == hearts) {
							//If the card is a heart, draw the heart icon in the first slot.
							tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, GameParameters::heart, 3, 7));

							//Set the colour of the text next to it to the heart colour.
							txt.setColor(sf::Color(255, 0, 0, 255));
						}

						//Set the text to the value of the card's effect and draw it.
						if (currentCards[k][j].getCardRank() == 11 && currentCards[k][j].getCardSuit().getSuitName() == clubs) {
							txt.setString("?");
						}
						else if (currentCards[k][j].getCardRank() == 12 && currentCards[k][j].getCardSuit().getSuitName() == clubs) {
							txt.setString("0");
						}
						else if (currentCards[k][j].getCardSuit().getSuitName() == clubs || currentCards[k][j].getCardSuit().getSuitName() == hearts) {
							txt.setString(std::to_string((int)currentCards[k][j].getCardEffect().getValue()));
						}
						else {
							txt.setString("");
						}

						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, txt, 9, 7));

						//Set the text to the value of the card's health and draw it.
						txt.setString(std::to_string((int)currentCards[k][j].getCardHealth()));
						txt.setColor(sf::Color(255, 0, 0, 255));
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, txt, 9, 16));


						//Set the text to the value of the card's diamond effect and draw it.
						txt.setString(std::to_string((int)currentCards[k][j].getEffectIncreases()));
						txt.setColor(sf::Color(235, 134, 27, 255));
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, txt, 9, 25));

						//SHOULD SHOW THE SPADE EFFECT BUT CURRENTLY DOESNT WORK.
						txt.setString(std::to_string((int)(1.f / currentCards[k][j].getDamageDecrease())));
						txt.setColor(sf::Color(0, 0, 0, 255));
						tile.addCardDescBarSprite(setPositionRelativeToCardDescBar(tile, txt, 9, 34));
					}


				}

				//otherwise just show the back of the card the represent an "empty" board spot (can just not render maybe)
				else {
					s = sf::Sprite(GameParameters::spritesheet);
					
					s.setTextureRect(
						sf::IntRect(
							sf::Vector2i(
								(13) * GameParameters::tileWidth,
								(0) * GameParameters::tileHeight),
							sf::Vector2i(
								GameParameters::tileWidth,
								GameParameters::tileHeight)));
					tile.setOccupied(false);
				}

				s.setPosition(tile.getX() * (GameParameters::tileWidth + GameParameters::cardDescBarWidth),
					tile.getY() * GameParameters::tileHeight + GameParameters::healthBarHeight);

				//apply sprite to tile
				tile.setCardSprite(s);

				//add tile to dictionary
				maps[k]->at(p->getPlayerNumber()).push_back(tile);
			}
		}
	}

	for (int i = 0; i < maps.size(); i++) {
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < maps.at(i)->at(j + 1).size(); k++) {
				window.draw(maps.at(i)->at(j + 1).at(k).getShape());
				window.draw(maps.at(i)->at(j + 1).at(k).getCardSprite());
				maps.at(i)->at(j + 1).at(k).drawCardDescBarSprite(window);
			}
		}
	}

	//1 is player num, 2 is position in hand array
	//_playerHandTiles[1][2];

	//1 is player num, 0 is position on board array
	//_playerBoardTiles[1][0];

}

