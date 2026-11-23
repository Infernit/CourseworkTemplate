#include "board.h"
#include <SFML/Graphics.hpp>
// For cerr
#include <iostream>
// Accessible throughout, cannot be const
std::vector<sf::Sprite> Board::cards;

// LNK2001 unresolved external symbol "public: static class std::vector<class sf::Sprite,class std::allocator<class sf::Sprite> > Board::Board::cards" (?Board::cards@Board@@2V?$vector@VSprite@sf@@V?$allocator@VSprite@sf@@@std@@@std@@A)
// LNK1120 1 unresolved externals

// make tiles as wide as Board::cards (not as tall so tiles can remain sqaure??? investigate)
const int Board::tileWidth = 34;
const int Board::tileHeight = 46; //46 test

// set board window size to be 15 (7 Board::cards + 4 spaces either side) tiles wide and 6 tiles tall
unsigned int Board::windowWidth = Board::tileWidth * 15;
unsigned int Board::windowHeight = Board::tileHeight * 6;

// Accessible throughout. For drag drop testing
sf::Sprite cardTest1(GameParameters::spritesheet);

// Check if the spritesheet exists
void Board::init() {

    // Put sprites on tiles (?)
    // Put somewhere else (console spam) later. Keep now for testing

    // Use string(RESOURCE_DIR) to get the resource directory path across multiple computers (?) without needing to copy sprite_sheet.png as path
    std::string sprite_path = std::string(RESOURCE_DIR) + "/img/sprite_sheet.png";
    std::cout << "Loading spritesheet from: " << sprite_path << std::endl;

    if (!GameParameters::spritesheet.loadFromFile(sprite_path)) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

	std::string font_path = std::string(RESOURCE_DIR) + "/txt/PublicPixel.otf";
	std::cout << "Loading font from: " << font_path << std::endl;

	if (!GameParameters::font.loadFromFile(font_path)) {
		std::cerr << "Failed to load font!" << std::endl;
	}

    // Make individual chards accessible from this
    //sf::Texture spritesheet;

    // cut it
	/*
    Suit suit(spades, GameParameters::getSpadeEffect());
    Card randomCard(suit, 5);

    cardTest1 = cutCard(randomCard);

    // Set new position to current grid position using mouse

    
    cardTest1.setPosition(sf::Vector2f(
        0,
        0
    ));
    

    Board::cards.push_back(cardTest1);
    */

    // Test multiple cards later

}

/*
    // window should recognise where mouse is
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
*/

// Make the card moveable (drag and drop) with mouse
sf::Vector2f pixelsToGrid(sf::Vector2f mousePos) {
	int gridX = static_cast<int>(mousePos.x) / Board::tileWidth;
	int gridY = static_cast<int>(mousePos.y) / Board::tileHeight;
	return sf::Vector2f(gridX, gridY);
}

// Pick up a card and move it
// Restrict it to only be able to be moved to unoccupied + certain tiles later ...

// its position on the grid (x, y) in tiles, should be converted pixels
sf::Vector2f Board::gridToPixels(int gridX, int gridY) {
	return sf::Vector2f(gridX * tileWidth, gridY * tileHeight);
}

Board::Board()  {
    _player1BoardCards = {};
    _player2BoardCards = {};
	
    init();
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
		if (cards->size() < GameParameters::boardSize) {
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

std::vector<Card>& Board::getEnemyCards(Player* player) {
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player2BoardCards;
	}
	else {
		return _player1BoardCards;
	}
}

std::vector<Card>& Board::getFriendlyCards(Player* player) {
	removeDeadCards();

	if (player->getPlayerNumber() == 1) {
		return _player1BoardCards;
	}
	else {
		return _player2BoardCards;
	}
}

bool Board::getIsEnemyAttackable(Player* player) {
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

void Board::removeDeadCards() {
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

bool Board::tryPlayCardToEffectable(Player* player, Player* opponent, Card& card) {
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
			<< GameParameters::cardNames[card.getCardRank()]
			<< " of "
			<< GameParameters::suitNames[card.getCardSuit().getSuitName()]
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

void Board::setPlayerCardsUsable(Player* player) {
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

sf::Sprite Board::cutCard(Card card) {
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

std::vector<Card>& Board::getPlayer1BoardCards() {
	return _player1BoardCards;
}

std::vector<Card>& Board::getPlayer2BoardCards() {
	return _player2BoardCards;
}

void Board::placeCardsOnBoard(Player* p1, Player* p2, sf::RenderWindow& window) {

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

	//TEST TEXT
	sf::Text text;
	text.setFont(GameParameters::font);
	text.setCharacterSize(10);
	text.setString("test");
	text.setPosition(100, 100);
	window.draw(text);

	sf::Sprite temp;

	//PLAYER 1
	//Hand
	for (int i = 0; i < p1->getHand().size(); i++) {
		temp = cutCard(p1->getHand()[i]);
		temp.setPosition((4 + i) * GameParameters::tileWidth + 4 + i, 5 * GameParameters::tileHeight + 5);
		window.draw(temp);
	}

	//Board
	for (int i = 0; i < _player1BoardCards.size(); i++) {
		temp = cutCard(_player1BoardCards[i]);
		temp.setPosition((4 + i) * GameParameters::tileWidth + 4 + i, 3 * GameParameters::tileHeight + 3);
		window.draw(temp);
	}

	//PLAYER 2
	//Hand
	for (int i = 0; i < p2->getHand().size(); i++) {
		temp = cutCard(p2->getHand()[i]);
		temp.setPosition((4 + i) * GameParameters::tileWidth + 4 + i, 0);
		window.draw(temp);
	}

	//Board
	for (int i = 0; i < _player2BoardCards.size(); i++) {
		temp = cutCard(_player2BoardCards[i]);
		temp.setPosition((4 + i) * GameParameters::tileWidth + 4 + i, 2 * GameParameters::tileHeight + 2);
		window.draw(temp);
	}


	//place cards in specific locations
}
