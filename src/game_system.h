#pragma once
#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

class Player;
class Board;
class Tile;
class Card;

struct GameSystem {
//________________________________//
//          CONSTRUCTORS          //
//________________________________//
	GameSystem();
	~GameSystem();
	
//_______________________________//
//          EVENT HOOKS          //
//_______________________________//
	void hookPlayerKilled(Player* player);
	void unhookPlayerKilled(Player* player);

//___________________________//
//          METHODS          //
//___________________________//
	void init();
	void reset();
	void clean();
	void update(const float& dt, sf::RenderWindow& window);
	void render(sf::RenderWindow& window);

	void nextTurn();
	void playerKilledHandler(int playerNumber);
	void createPlayers(bool isP2Ai);
	static void raiseMaxEnergy();

//____________________________//
//          GETTTERS          //
//____________________________//
	int getNextPlayerNumber();
	Player* getPlayer1();
	Player* getPlayer2();
	static int getMaxEnergy();
	int getTurn();
	bool getSkipTurn();
	Board* getBoard();
	
//___________________________//
//          SETTERS          //
//___________________________//
	static void setMaxEnergy(int value);
	void setSkipTurn(bool value);

private:
//___________________________________//
//          LOCAL VARIABLES          //
//___________________________________//
	std::unique_ptr<Player> _player1;
	std::unique_ptr<Player> _player2;
	static int _playerNumber;
	static int _maxEnergy;

	int _turn;
	bool _skipNextTurn;

	std::unique_ptr<Board> _board;

	bool _draggingCard;
	Card* _cardBeingDragged;
	sf::Sprite* _cardSpriteBeingDragged;
	Tile* _tileBeingDragged;
};