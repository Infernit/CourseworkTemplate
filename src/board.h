#pragma once
#include "card.h"
#include "game_parameters.h"
#include <vector>
#include <SFML/Graphics.hpp>
// For tile occupation tracking
//#include <map>
#include "tile.h"

/// <summary>
/// Class for board rendering and card handling.
/// </summary>
class Board {

public:
	/// <summary>
	/// Constructor
	/// </summary>
	Board(GameSystem* system);
	// Maps
	std::map<std::pair<int,int>, bool> occupiedPlayer1Tiles;
	std::map<std::pair<int, int>, bool> occupiedPlayer2Tiles;
	std::vector<Tile> boardTiles;

	/// <summary>
	/// Converts a px position into the same location on the grid.
	/// </summary>
	/// <param name="mousePos">Px location on the grid.</param>
	/// <returns>Location on grid.</returns>
	sf::Vector2f pixelsToGrid(sf::Vector2f mousePos);

	/// <summary>
	/// Converts a grid position into the same location in px.
	/// </summary>
	/// <param name="gridX">X location on the grid.</param>
	/// <param name="gridY">Y location on the grid.</param>
	/// <returns>Location in px.</returns>
	sf::Vector2f gridToPixels(int gridX, int gridY);

	//
	sf::Vector2f getCardPosition(sf::Sprite cardSprite);
	//
	void Board::makeValidPlayTilesGlowGreen(int yValue);

	/// <summary>
	/// Plays the referenced card. Either just plays to board if H or C, or plays to target if D or S.
	/// </summary>
	/// <param name="player">Player who played the card.</param>
	/// <param name="opponent">Player who didn't play the card.</param>
	/// <param name="card">The card that was played.</param>
	/// <returns>True if succeeded, false if failed.</returns>
	bool playCard(Player* player, Player* opponent, Card& card);

	bool effectEnemyKingOfHearts(Player* player, Effect effect);

	/// <summary>
	/// Gets the cards on the board for the player parameter.
	/// </summary>
	/// <param name="player">Player to get the cards of.</param>
	/// <returns>Player's cards.</returns>
	std::vector<Card>& getFriendlyCards(Player* player);

	std::vector<Card>& getFriendlyGraveyardCards(Player* player);

	/// <summary>
	/// Gets the cards on the board for the opponent of the player parameter.
	/// </summary>
	/// <param name="player">Player to get the opponent's cards of.</param>
	/// <returns>Opponent's cards.</returns>
	std::vector<Card>& getEnemyCards(Player* player);

	/// <summary>
	/// Gets whether the player has any clubs on their board.
	/// </summary>
	/// <param name="player">Player to check.</param>
	/// <returns>True if player has no clubs on their board, otherwise false.</returns>
	bool getIsEnemyAttackable(Player* player);

	/// <summary>
	/// Erases any cards on the board from either player that are dead.
	/// </summary>
	void removeDeadCards();

	bool playCardRankAndSuit(Player* player, Player* opponent, Card& card);

	/// <summary>
	/// Tries to apply the effect of a card to an effectable target.
	/// </summary>
	/// <param name="player">Player who played the card.</param>
	/// <param name="opponent">Opponent of player who played the card.</param>
	/// <param name="card">Reference to card played.</param>
	/// <returns>True if card was played, otherwise false.</returns>
	bool tryPlayCardToEffectable(Player* player, Player* opponent, Card& card);
	bool jackSpadeEffectable(Player* opponent);
	bool jackDiamondEffectable(Player* player);
	
	void resetDamageDebuffs(Player* player);

	bool queenHeartsEffectable(Player* player);
	bool queenClubsEffectable(Player* player);
	bool queenSpadeEffectable(Player* player);
	bool queenDiamondEffectable(Player* player);

	bool graveyardTemplate(Player* player, int num);

	bool kingSpadeEffectable(Player* player);
	bool kingDiamondEffectable(Player* player);
	bool isKingOfHeartsOnBoard(Player* opponent); 

	bool aceSpadeEffectable(Player* player);
	bool aceDiamondEffectable(Player* player);
	bool aceClubsEffectable(Player* player);
	bool aceHeartsEffectable(Player* player);

	/// <summary>
	/// Sets all cards of the referenced player to be usable.
	/// </summary>
	/// <param name="player">Player to make cards usable.</param>
	void setPlayerCardsUsable(Player* player);

	/// <summary>
	/// Cuts out the relevant sprite from the spritesheet based on the card parameter.
	/// </summary>
	/// <param name="card">Card to cut.</param>
	/// <returns>Sprite of the card to be cut.</returns>
	sf::Sprite cutCard(Card card);

	/// <summary>
	/// Renders the whole board to a window.
	/// </summary>
	/// <param name="p1">Player 1, to get their hand contents.</param>
	/// <param name="p2">Player 2, to get their hand contents.</param>
	/// <param name="window">Window to render to.</param>
	void placeCardsOnBoard(Player* p1, Player* p2, sf::RenderWindow& window);

	void changeTileToOccupied(int xVal, int yVal);
	Tile Board::getTileFromBoardtiles(int xVal, int yVal);

private:
	/// <summary>
	/// Vector containing all of player 1's cards on the board.
	/// </summary>
	std::vector<Card> _player1BoardCards;

	/// <summary>
	/// Vector containing all of player 2's cards on the board.
	/// </summary>
	std::vector<Card> _player2BoardCards;

	std::vector<Card> _player1GraveyardCards;
	std::vector<Card> _player2GraveyardCards;

	GameSystem* _system;
};