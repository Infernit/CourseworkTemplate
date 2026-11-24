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

Board::Board()  {
	//Set both player's cards to empty.
    _player1BoardCards = {};
    _player2BoardCards = {};
	// Set graveyard cards
	_player1GraveyardCards = {};
	_player2GraveyardCards = {};
	
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

	/*
    // get window to obey width and height constants
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML works!");

    // Practical legacy
 
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    init();
    bool draggingCard = false;
    
    while (window.isOpen()) {

        bool allowedToMove = true;

        // Grid ? of tiles....
        for (int x = 0; x < windowWidth / tileWidth; x++) {

            for (int y = 0; y < windowHeight / tileHeight; y++) {

                sf::RectangleShape tile(sf::Vector2f(tileWidth, tileHeight));

                tile.setPosition(x * tileWidth, y * tileHeight);

                // Make board green
                tile.setFillColor(sf::Color::Green);
                tile.setOutlineThickness(1.f);
                tile.setOutlineColor(sf::Color::Black);

                window.draw(tile);

            }

        }

        // Interactable tiles (using mouse...)
         // window should recognise where mouse is
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // breakpoint to check mouse position
        // Continously calculates as prog runs (good)
        int currentTileX = mousePos.x / Board::tileWidth;
        int currentTileY = mousePos.y / Board::tileHeight;

        // highlights (reactive)
        // do not work in fs, only minimised / default window
        sf::RectangleShape highlightTile(sf::Vector2f(Board::tileWidth, Board::tileHeight));

        highlightTile.setPosition(currentTileX * Board::tileWidth, currentTileY * Board::tileHeight);
        highlightTile.setFillColor(sf::Color(255, 255, 0, 100)); // Yellow with transparency  
        window.draw(highlightTile);

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // disable movement for now 
            
            // Mouse drags card
			if (event.type == sf::Event::MouseButtonPressed) {

				if (event.mouseButton.button == sf::Mouse::Left) {

                    // test statement
                    std::cout << "MOUSE INTERACT\n";

					// Get mouse position
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					// Convert to grid coordinates
                    // Print out grid positions (test passed)
					sf::Vector2f gridPos = pixelsToGrid(sf::Vector2f(mousePos));
					std::cout << "Mouse pressed at grid position: (" << gridPos.x << ", " << gridPos.y << ")" << std::endl;

                    // Prepare for future logic with allowed to move var
                    if (cardTest1.getGlobalBounds().contains(
                        static_cast<float>(mousePos.x),
                        static_cast<float>(mousePos.y))
                        && allowedToMove == true) {
                        draggingCard = true;
                    }

				}
			}

            // Mouse releases card
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    std::cout << "MOUSE RELEASE\n";

                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f gridPos = pixelsToGrid(sf::Vector2f(mousePos));
                    std::cout << "Mouse released at grid position: (" << gridPos.x << ", " << gridPos.y << ")" << std::endl;

                    // Only move it if the tile it was on was interacted with ?
                    if (draggingCard == true) {
                        cardTest1.setPosition(gridPos.x * Board::tileWidth, gridPos.y * Board::tileHeight);
                    }

                    // reset to default val
                    draggingCard = false;
                }
            }
            
        }

        //window.draw(cardTest1);
        window.display();
		        
    }
	*/
}

bool Board::playCard(Player* player, Player* opponent, Card& card) {
	//Don't let the card be played if the player doesn't have enough energy.
	if (player->getCurrentEnergy() < card.getCardRank()) {
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
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardRank());
			//Card played successfully.
			return true;
		}
	}

	// Cards that are played straight from the hand.
	else {
		// Try to play the card.
		if (tryPlayCardToEffectable(player, opponent, card)) {
			//If succeeds remove card from hand and reduce player energy by card cost.
			player->removeHandCard(card);
			// Then add to graveyard
			player->addToGraveyard(card);
			player->setCurrentEnergy(player->getCurrentEnergy() - card.getCardRank());
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

// PINEAPPLE
void Board::removeDeadCards() {
	int j = 0;

	//Loop through all player 1 cards
	for (int i = 0; i < _player1BoardCards.size(); i++) {
		if (_player1BoardCards[i].getIsDead()) {
			// Add to the graveyard
			_player1GraveyardCards.push_back(_player1BoardCards[i - j]);
			//If card is dead erase it from the list.
			_player1BoardCards.erase(_player1BoardCards.begin() + i - j);
			//Increment removed cards.
			j++;
		}
	}

	j = 0;

	//Loop through all player 2 cards
	for (int i = 0; i < _player2BoardCards.size(); i++) {
		if (_player2BoardCards[i].getIsDead()) {
			// Add to the graveyard
			_player2GraveyardCards.push_back(_player2BoardCards[i - j]);
			//If card is dead erase it from the list.
			_player2BoardCards.erase(_player2BoardCards.begin() + i - j);
			//Increment removed cards.
			j++;
		}
	}
}

bool Board::tryPlayCardToEffectable(Player* player, Player* opponent, Card& card) {
	
	std::vector<Card>* cardsToApplyTo;
	Player* playerToApplyTo;
	int index = 1;

	// Apply card to enemy.
	if (card.getCardSuit().getSuitName() == clubs || card.getCardSuit().getSuitName() == spades) {
		cardsToApplyTo = &getEnemyCards(player);
		playerToApplyTo = opponent;
	}

	// Apply card to ally.
	else {
		cardsToApplyTo = &getFriendlyCards(player);
		playerToApplyTo = player;
	}

	//Flag lowered by default.
	bool canHaveZeroElements = false;

	//If opponent is attackable, and card is a club, opposing player is a target.
	if (getIsEnemyAttackable(player) && card.getCardSuit().getSuitName() == clubs) {
		std::cout
			<< "0: Opposing Player"
			<< std::endl;
		canHaveZeroElements = true;
	}
	//If card is a heart, current player is a target.
	else if (card.getCardSuit().getSuitName() == hearts) {
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
	for (Card card : *cardsToApplyTo) {
		std::cout
			<< index
			<< ": "
			<< GameParameters::cardNames[card.getCardRank()]
			<< " of "
			<< GameParameters::suitNames[card.getCardSuit().getSuitName()]
			<< std::endl;
		index++;
	}

	//Allow player to choose card / player to apply effect to.
	std::cout << "Pick card to effect: ";
	int num;
	std::cin >> num;

	//Apply card to target card.
	if (num <= cardsToApplyTo->size() && num > 0) {
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

	// potential issue / may require different function in card (?)
	std::vector<Card>* cardsToApplyTo = &opponent->getHand();

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		cardsToApplyTo->at(i).setCardEnergyCost(cardsToApplyTo->at(i).getCardEnergyCost() * 2);
	}

}

bool Board::jackDiamondEffectable(Player* player) {

	// potential issue / may require different function in card (?)
	std::vector<Card>* cardsToApplyTo = &player->getHand();

	for (int i = 0; i < cardsToApplyTo->size(); i++) {
		cardsToApplyTo->at(i).setCardEnergyCost(cardsToApplyTo->at(i).getCardEnergyCost() / 2);
	}

}

// PINEAPPLE
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
		cards->at(i).setIsUsable(true);
	}
}

// PINEAPPLE
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

void Board::placeCardsOnBoard(Player* p1, Player* p2, sf::RenderWindow& window) {

	//========================================================//
	//---THIS FUNCTION IS A WIP AND VERY MUCH NOT EFFICIENT---//
	//========================================================//

	// shhhhhhhhhhh yes it is ..... ^^^

	//Create tiles
	
	// Regular board
	// Change so only half
	// Its only supposed to be 15 tiles wide
	for (int x = 0; x < ((int)(GameParameters::windowWidth /
		// Make sure extra space of decor accounted for
		(GameParameters::tileWidth + GameParameters::cardDescBarWidth))
		/ 2); x++) {

		for (int y = 0; y < GameParameters::windowHeight / GameParameters::tileHeight - 1; y++) {

			//Tiles should be of card width (tileWidth) + card desc bar width and card height (tileHeight).
			sf::RectangleShape tile(sf::Vector2f(GameParameters::tileWidth + GameParameters::cardDescBarWidth, GameParameters::tileHeight));

			//Set position based on the size and loop.
			tile.setPosition(x * (GameParameters::tileWidth + GameParameters::cardDescBarWidth), y * GameParameters::tileHeight + GameParameters::healthBarHeight);

			// Make board yellow to test moving green health bar
			tile.setFillColor(sf::Color::Yellow);
			tile.setOutlineThickness(1.f);
			tile.setOutlineColor(sf::Color::Black);

			window.draw(tile);
		}
	}

	// Last value it was on for blue grid?
	for (int x = (((int)(GameParameters::windowWidth / (GameParameters::tileWidth + GameParameters::cardDescBarWidth)) / 2));
		// Must be less than the max width
		x < ((int)(GameParameters::windowWidth / (GameParameters::tileWidth + GameParameters::cardDescBarWidth))); x++) {

		for (int y = 0; y < GameParameters::windowHeight / GameParameters::tileHeight - 1; y++) {

			sf::RectangleShape tile(sf::Vector2f(GameParameters::tileWidth + GameParameters::cardDescBarWidth, GameParameters::tileHeight));

			tile.setPosition(x * (GameParameters::tileWidth + GameParameters::cardDescBarWidth), y * GameParameters::tileHeight + GameParameters::healthBarHeight);

			// Make board blue to contrast
			tile.setFillColor(sf::Color::Cyan);
			tile.setOutlineThickness(1.f);
			tile.setOutlineColor(sf::Color::Black);

			window.draw(tile);
		}

	}

	//Temp sprite storing variable.
	sf::Sprite tempSprite;

	//Create text object using font for cardDescBar.
	sf::Text tempText;
	tempText.setFont(GameParameters::font);
	tempText.setCharacterSize(4);

	//Temp position variables to prevent doing calculations multiple times.
	int tempPosX = 0;
	int tempPosY = 0;

	//PLAYER 1
	//Hand
	for (int i = 0; i < p1->getHand().size(); i++) {
		//Cut each hand card.
		tempSprite = cutCard(p1->getHand()[i]);

		//Place card in relevant location based on loop.
		tempSprite.setPosition(
			(4 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth),
			5 * GameParameters::tileHeight + GameParameters::healthBarHeight);

		//Draw card in window.
		window.draw(tempSprite);
	}

	//Board
	for (int i = 0; i < _player1BoardCards.size(); i++) {
		//Cut each board card.
		tempSprite = cutCard(_player1BoardCards[i]);

		//Set temp variables to position of card.
		tempPosX = (4 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth);
		tempPosY = 3 * GameParameters::tileHeight + GameParameters::healthBarHeight;

		//Set location based on temp variables.
		tempSprite.setPosition(tempPosX, tempPosY);

		//Draw card in window.
		window.draw(tempSprite);

		//Move cardDescBar to next to the card and draw it.
		GameParameters::cardDescBar.setPosition(tempPosX + GameParameters::tileWidth, tempPosY);
		window.draw(GameParameters::cardDescBar);

		if (_player1BoardCards[i].getCardSuit().getSuitName() == clubs) {
			//If the card is a club, draw the club icon in the first slot.
			GameParameters::club.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::club);

			//Set the colour of the text next to it to the club colour.
			tempText.setColor(sf::Color(91, 110, 225, 255));
		}
		else {
			//If the card is a heart, draw the heart icon in the first slot.
			GameParameters::heart.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::heart);

			//Set the colour of the text next to it to the heart colour.
			tempText.setColor(sf::Color(255, 0, 0, 255));
		}

		//Set the text to the value of the card's effect and draw it.
		tempText.setString(std::to_string((int)_player1BoardCards[i].getCardEffect().getValue()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 7);
		window.draw(tempText);

		//Set the text to the value of the card's health and draw it.
		tempText.setString(std::to_string((int)_player1BoardCards[i].getCardHealth()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 16);
		tempText.setColor(sf::Color(255, 0, 0, 255));
		window.draw(tempText);

		//Set the text to the value of the card's diamond effect and draw it.
		tempText.setString(std::to_string((int)_player1BoardCards[i].getEffectIncreases()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 25);
		tempText.setColor(sf::Color(235, 134, 27, 255));
		window.draw(tempText);

		//SHOULD SHOW THE SPADE EFFECT BUT CURRENTLY DOESNT WORK.
		tempText.setString(std::to_string((int)(1.f / _player1BoardCards[i].getDamageDecrease())));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 34);
		tempText.setColor(sf::Color(0, 0, 0, 255));
		window.draw(tempText);
	}

	//PLAYER 1
	//Board
	for (int i = 0; i < _player1GraveyardCards.size(); i++) {
		//Cut each board card.
		tempSprite = cutCard(_player1GraveyardCards[i]);

		//Set temp variables to position of card.
		tempPosX = (15 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth);
		tempPosY = 3 * GameParameters::tileHeight + GameParameters::healthBarHeight;

		//Set location based on temp variables.
		tempSprite.setPosition(tempPosX, tempPosY);

		//Draw card in window.
		window.draw(tempSprite);

		//Move cardDescBar to next to the card and draw it.
		GameParameters::cardDescBar.setPosition(tempPosX + GameParameters::tileWidth, tempPosY);
		window.draw(GameParameters::cardDescBar);

		if (_player1GraveyardCards[i].getCardSuit().getSuitName() == clubs) {
			//If the card is a club, draw the club icon in the first slot.
			GameParameters::club.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::club);
			//Set the colour of the text next to it to the club colour.
			tempText.setColor(sf::Color(91, 110, 225, 255));
		}
		else {
			//If the card is a heart, draw the heart icon in the first slot.
			GameParameters::heart.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::heart);

			//Set the colour of the text next to it to the heart colour.
			tempText.setColor(sf::Color(255, 0, 0, 255));
		}

		//Set the text to the value of the card's effect and draw it.
		tempText.setString(std::to_string((int)_player1GraveyardCards[i].getCardEffect().getValue()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 7);
		window.draw(tempText);

		//Set the text to the value of the card's health and draw it.
		tempText.setString(std::to_string((int)_player1GraveyardCards[i].getCardHealth()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 16);
		tempText.setColor(sf::Color(255, 0, 0, 255));
		window.draw(tempText);

		//Set the text to the value of the card's diamond effect and draw it.
		tempText.setString(std::to_string((int)_player1GraveyardCards[i].getEffectIncreases()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 25);
		tempText.setColor(sf::Color(235, 134, 27, 255));
		window.draw(tempText);

		//SHOULD SHOW THE SPADE EFFECT BUT CURRENTLY DOESNT WORK.
		tempText.setString(std::to_string((int)(1.f / _player1GraveyardCards[i].getDamageDecrease())));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 34);
		tempText.setColor(sf::Color(0, 0, 0, 255));
		window.draw(tempText);
	}

	//PLAYER 2
	//Hand
	for (int i = 0; i < p2->getHand().size(); i++) {
		//Cut each hand card.
		tempSprite = cutCard(p2->getHand()[i]);

		//Place card in relevant location based on loop.
		tempSprite.setPosition(
			(4 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth), 
			GameParameters::healthBarHeight);

		//Draw card in window.
		window.draw(tempSprite);
	}

	//Board
	for (int i = 0; i < _player2BoardCards.size(); i++) {
		//Cut each board card.
		tempSprite = cutCard(_player2BoardCards[i]);

		//Set temp variables to position of card.
		tempPosX = (4 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth);
		tempPosY = 2 * GameParameters::tileHeight + GameParameters::healthBarHeight;

		//Set location based on temp variables.
		tempSprite.setPosition(tempPosX, tempPosY);

		//Draw card in window.
		window.draw(tempSprite);

		//Move cardDescBar to next to the card and draw it.
		GameParameters::cardDescBar.setPosition(tempPosX + GameParameters::tileWidth, tempPosY);
		window.draw(GameParameters::cardDescBar);

		if (_player2BoardCards[i].getCardSuit().getSuitName() == clubs) {
			//If the card is a club, draw the club icon in the first slot.
			GameParameters::club.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::club);

			//Set the colour of the text next to it to the club colour.
			tempText.setColor(sf::Color(91, 110, 225, 255));
		}
		else {
			//If the card is a heart, draw the heart icon in the first slot.
			GameParameters::heart.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::heart);

			//Set the colour of the text next to it to the heart colour.
			tempText.setColor(sf::Color(255, 0, 0, 255));
			
		}

		//Set the text to the value of the card's effect and draw it.
		tempText.setString(std::to_string((int)_player2BoardCards[i].getCardEffect().getValue()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 7);
		window.draw(tempText);

		//Set the text to the value of the card's health and draw it.
		tempText.setString(std::to_string((int)_player2BoardCards[i].getCardHealth()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 16);
		tempText.setColor(sf::Color(255, 0, 0, 255));
		window.draw(tempText);

		//Set the text to the value of the card's diamond effect and draw it.
		tempText.setString(std::to_string((int)_player2BoardCards[i].getEffectIncreases()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 25);
		tempText.setColor(sf::Color(235, 134, 27, 255));
		window.draw(tempText);

		//SHOULD SHOW THE SPADE EFFECT BUT CURRENTLY DOESNT WORK.
		tempText.setString(std::to_string((int)(1.f / _player2BoardCards[i].getDamageDecrease())));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 34);
		tempText.setColor(sf::Color(0, 0, 0, 255));
		window.draw(tempText);
	}
	
	//PLAYER 2
	//Graveyard
	for (int i = 0; i < _player2GraveyardCards.size(); i++) {
		//Cut each board card.
		tempSprite = cutCard(_player2GraveyardCards[i]);

		//Set temp variables to position of card.
		tempPosX = (15 + i) * (GameParameters::tileWidth + GameParameters::cardDescBarWidth);
		tempPosY = 2 * GameParameters::tileHeight + GameParameters::healthBarHeight;

		//Set location based on temp variables.
		tempSprite.setPosition(tempPosX, tempPosY);

		//Draw card in window.
		window.draw(tempSprite);

		//Move cardDescBar to next to the card and draw it.
		GameParameters::cardDescBar.setPosition(tempPosX + GameParameters::tileWidth, tempPosY);
		window.draw(GameParameters::cardDescBar);

		if (_player2GraveyardCards[i].getCardSuit().getSuitName() == clubs) {
			//If the card is a club, draw the club icon in the first slot.
			GameParameters::club.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::club);
			//Set the colour of the text next to it to the club colour.
			tempText.setColor(sf::Color(91, 110, 225, 255));
		}
		else {
			//If the card is a heart, draw the heart icon in the first slot.
			GameParameters::heart.setPosition(tempPosX + GameParameters::tileWidth + 3, tempPosY + 7);
			window.draw(GameParameters::heart);

			//Set the colour of the text next to it to the heart colour.
			tempText.setColor(sf::Color(255, 0, 0, 255));
		}

		//Set the text to the value of the card's effect and draw it.
		tempText.setString(std::to_string((int)_player2GraveyardCards[i].getCardEffect().getValue()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 7);
		window.draw(tempText);

		//Set the text to the value of the card's health and draw it.
		tempText.setString(std::to_string((int)_player2GraveyardCards[i].getCardHealth()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 16);
		tempText.setColor(sf::Color(255, 0, 0, 255));
		window.draw(tempText);

		//Set the text to the value of the card's diamond effect and draw it.
		tempText.setString(std::to_string((int)_player2GraveyardCards[i].getEffectIncreases()));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 25);
		tempText.setColor(sf::Color(235, 134, 27, 255));
		window.draw(tempText);

		//SHOULD SHOW THE SPADE EFFECT BUT CURRENTLY DOESNT WORK.
		tempText.setString(std::to_string((int)(1.f / _player2GraveyardCards[i].getDamageDecrease())));
		tempText.setPosition(tempPosX + GameParameters::tileWidth + 9, tempPosY + 34);
		tempText.setColor(sf::Color(0, 0, 0, 255));
		window.draw(tempText);
	}

	
	// Player 2 healthbar space
	
	sf::RectangleShape healthbarPlayer2Red(sf::Vector2f((GameParameters::windowWidth / 2), GameParameters::healthBarHeight));
	// make sure its being positioned correctly
	healthbarPlayer2Red.setPosition(0.f, 0.f);
	healthbarPlayer2Red.setFillColor(sf::Color::Red);
	window.draw(healthbarPlayer2Red);

	// Place a green on top that will decrease in size as player takes damage
	sf::RectangleShape healthbarPlayer2(sf::Vector2f((float)(GameParameters::windowWidth / 2)* (float)p2->getHealth() / (float)GameParameters::maxPlayerHealth, GameParameters::healthBarHeight));
	healthbarPlayer2.setPosition(0.f, 0.f);
	healthbarPlayer2.setFillColor(sf::Color::Green);
	window.draw(healthbarPlayer2);

	//Player 1 healthbar
	sf::RectangleShape healthbarPlayer1Red(sf::Vector2f((GameParameters::windowWidth / 2), GameParameters::healthBarHeight));
	// make sure its being positioned correctly
	healthbarPlayer1Red.setPosition(0.f, (GameParameters::tileHeight * 6) + GameParameters::healthBarHeight);
	healthbarPlayer1Red.setFillColor(sf::Color::Red);
	window.draw(healthbarPlayer1Red);

	// Place a green on top that will decrease in size as player takes damage
	sf::RectangleShape healthbarPlayer1(sf::Vector2f((float)(GameParameters::windowWidth / 2)* (float)p1->getHealth() / (float)GameParameters::maxPlayerHealth, GameParameters::healthBarHeight));
	// To account for lines (1px each)
	healthbarPlayer1.setPosition(0.f, (GameParameters::tileHeight * 6) + GameParameters::healthBarHeight);
	healthbarPlayer1.setFillColor(sf::Color::Green);
	window.draw(healthbarPlayer1);
}
