#include "game_system.h"
#include "player.h"
#include "game_parameters.h"
#include "board.h"

#include <iostream>
#include <memory>
#include <vector>

//________________________________//
//          CONSTRUCTORS          //
//________________________________//
GameSystem::GameSystem() = default;
GameSystem::~GameSystem() = default;

//_______________________________//
//          EVENT HOOKS          //
//_______________________________//
// Event hook. Listens to "PlayerKilled" and runs "playerKilledHandler" when the event is invoked.
void GameSystem::hookPlayerKilled(Player* player) {
	__hook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

// Event unhook. Stops listening to "PlayerKilled".
void GameSystem::unhookPlayerKilled(Player* player) {
	__unhook(&Player::PlayerKilled, player, &GameSystem::playerKilledHandler);
}

//___________________________//
//          METHODS          //
//___________________________//
// Runs on game initialisation
void GameSystem::init() {
	GameSystem::createPlayers(false);

	_maxEnergy = GameParameters::startingEnergy;
	_player1.get()->setCurrentEnergy(_maxEnergy);
	_player2.get()->setCurrentEnergy(_maxEnergy);

	_player1.get()->fillHand();
	_player2.get()->fillHand();

	_board = std::make_unique<Board>(this);

	_turn = 1;
	_skipNextTurn = false;

	_draggingCard = false;
}

// Instantiates player1 & player2
void GameSystem::createPlayers(bool isP2Ai) {
	_player1 = std::make_unique<Player>(false, *this);
	_player2 = std::make_unique<Player>(false, *this);
}

void GameSystem::update(const float& dt, sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	// breakpoint to check mouse position
	// Continously calculates as prog runs (good)
	int currentTileX = mousePos.x / GameParameters::tileWidth;
	int currentTileY = mousePos.y / GameParameters::tileHeight;

	if (_draggingCard) {
		_board.get()->renderBoard(_player1.get(), _player2.get(), window);
		window.display();
	}

	sf::Event event;

	while (window.pollEvent(event)) {

		if (event.type == sf::Event::Closed) {
			window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed) {

			if (event.mouseButton.button == sf::Mouse::Left) {
				// Get tile the mouse clicked on. Prep for dragging.
				std::vector<std::map<int, std::vector<Tile>>*> mapsToCheck = _board.get()->getTileMaps();

				for (int i = 0; i < mapsToCheck.size(); i++) {
					for (int j = 1; j < 3; j++) {
						for (int k = 0; k < mapsToCheck[i]->at(j).size(); k++) {
							if (mapsToCheck[i]->at(j)[k].getShape().getGlobalBounds().contains(
								static_cast<float>(mousePos.x),
								static_cast<float>(mousePos.y))) {

								switch (i) {
								case 0:
									_cardBeingDragged = &(j == 1 ?
										_player1.get()->getHandRef()[k] :
										_player2.get()->getHandRef()[k]);
									break;
								case 1:
									_cardBeingDragged = &(j == 1 ?
										_board.get()->getFriendlyCards(_player1.get())[k] :
										_board.get()->getFriendlyCards(_player2.get())[k]);
									break;
								case 2:
									_cardBeingDragged = &(j == 1 ?
										_board.get()->getFriendlyGraveyardCards(_player1.get())[k] :
										_board.get()->getFriendlyGraveyardCards(_player2.get())[k]);
									break;
								}

								std::cout
									<< "Picked Up: "
									<< GameParameters::cardNames[_cardBeingDragged->getCardRank()]
									<< " of "
									<< GameParameters::suitNames[_cardBeingDragged->getCardSuit().getSuitName()]
									<< std::endl;


								std::cout 
									<< "Mouse Pressed in Tile: (" 
									<< mapsToCheck[i]->at(j)[k].getX() 
									<< "," 
									<< mapsToCheck[i]->at(j)[k].getY() 
									<< ")" 
									<< std::endl;

								std::string temp = "";

								if (i == 0) {
									temp = "Hand";
								}
								else if (i == 1) {
									temp = "Board";
								}
								else {
									temp = "Graveyard";
								}


								std::cout
									<< "This translates to: "
									<< std::endl
									<< "Player "
									<< j
									<< "'s "
									<< temp
									<< "."
									<< std::endl;

								_draggingCard = true;
								_cardSpriteBeingDragged = mapsToCheck[i]->at(j)[k].getCardSpriteRef();
								_tileBeingDragged = &mapsToCheck[i]->at(j)[k];
								mapsToCheck[i]->at(j)[k].setBeingDragged(true);
								break;
							}
						}
					}
				}

			}
		}

		if (event.type == sf::Event::MouseButtonReleased) {

			if (event.mouseButton.button == sf::Mouse::Left) {

				// Put card back where it came from (just default for now)
				_tileBeingDragged->setBeingDragged(false);
				_cardSpriteBeingDragged->setPosition(
					_tileBeingDragged->getX() * (GameParameters::tileWidth + GameParameters::cardDescBarWidth),
					_tileBeingDragged->getY() * GameParameters::tileHeight + GameParameters::healthBarHeight);
				_board.get()->renderBoard(_player1.get(), _player2.get(), window);
				window.display();

				std::vector<std::map<int, std::vector<Tile>>*> mapsToCheck = _board.get()->getTileMaps();

				for (int i = 0; i < mapsToCheck.size(); i++) {
					for (int j = 1; j < 3; j++) {
						for (int k = 0; k < mapsToCheck[i]->at(j).size(); k++) {
							if (mapsToCheck[i]->at(j)[k].getShape().getGlobalBounds().contains(
								static_cast<float>(mousePos.x),
								static_cast<float>(mousePos.y)) && _draggingCard) {
								std::cout
									<< "Mouse Released in Tile: ("
									<< mapsToCheck[i]->at(j)[k].getX()
									<< ","
									<< mapsToCheck[i]->at(j)[k].getY()
									<< ")"
									<< std::endl;

								std::string temp = "";

								if (i == 0) {
									temp = "Hand";
								}
								else if (i == 1) {
									temp = "Board";
								}
								else {
									temp = "Graveyard";
								}
									

								std::cout
									<< "This translates to: "
									<< std::endl
									<< "Player "
									<< j
									<< "'s "
									<< temp
									<< "."
									<< std::endl;

								// Do check for if dragged card can be where it was dragged to

								// If so swap card

								// Otherwise return to original tile

								break;
							}
						}
					}
				}

				_draggingCard = false;

				/*
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
				*/
			}
		}
	}
}

void GameSystem::render(sf::RenderWindow& window)
{
	_board->placeCardsOnBoard(_player1.get(), _player2.get(), window);
}

void GameSystem::nextTurn()
{
	if (_skipNextTurn) {
		_skipNextTurn = false;
		return;
	}

	if (_turn == 1) {
		_turn = 2;
	}
	else {
		_turn = 1;
	}
}

// Code that is run when event is invoked.
void GameSystem::playerKilledHandler(int playerNumber) {
	std::cout << playerNumber << " died" << std::endl;
}

void GameSystem::raiseMaxEnergy() {
	_maxEnergy++;
}

//____________________________//
//          GETTTERS          //
//____________________________//
// Returns the next player number
int GameSystem::getNextPlayerNumber() {
	GameSystem::_playerNumber++;
	return GameSystem::_playerNumber;
}

// Returns a pointer to player1
Player* GameSystem::getPlayer1() {
	return _player1.get();
}

// Returns a pointer to player2
Player* GameSystem::getPlayer2() {
	return _player2.get();
}

// Gets the current max energy
int GameSystem::getMaxEnergy() {
	return _maxEnergy;
}

int GameSystem::getTurn()
{
	return _turn;
}

bool GameSystem::getSkipTurn()
{
	return _skipNextTurn;
}

Board* GameSystem::getBoard()
{
	return _board.get();
}

//___________________________//
//          SETTERS          //
//___________________________//
void GameSystem::setMaxEnergy(int value) {
	_maxEnergy = value;
}

void GameSystem::setSkipTurn(bool value)
{
	_skipNextTurn = value;
}

//___________________________________//
//          LOCAL VARIABLES          //
//___________________________________//
int GameSystem::_playerNumber = 0;
int GameSystem::_maxEnergy = GameParameters::startingEnergy;