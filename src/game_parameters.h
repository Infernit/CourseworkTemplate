#pragma once
#include "effect.h"
#include "player.h"
#include "game_system.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

/// <summary>
/// A struct of Parameters that are used in multiple places across the program.
/// </summary>
struct GameParameters {
	/// <summary>
	/// A method that defines the effect of numbered hearts cards.
	/// </summary>
	/// <returns>Effect of numbered hearts cards.</returns>
	static Effect getHeartEffect();

	/// <summary>
	/// A method that defines the effect of numbered diamonds cards.
	/// </summary>
	/// <returns>Effect of numbered diamonds cards.</returns>
	static Effect getDiamondEffect();

	/// <summary>
	/// A method that defines the effect of numbered clubs cards.
	/// </summary>
	/// <returns>Effect of numbered clubs cards.</returns>
	static Effect getClubEffect();

	/// <summary>
	/// A method that defines the effect of numbered spades cards.
	/// </summary>
	/// <returns>Effect of numbered spades cards.</returns>
	static Effect getSpadeEffect();

	/// <summary>
	/// Maximum size of a player's hand (Currently 7).
	/// </summary>
	static int handSize;

	/// <summary>
	/// The energy that each player starts the game with (Currently 2).
	/// </summary>
	static int startingEnergy;

	/// <summary>
	/// The maximum health a player can have (Currently 100).
	/// </summary>
	static int maxPlayerHealth;

	/// <summary>
	/// The maximum size of a player's board (Currently 5).
	/// </summary>
	static int boardSize;

	/// <summary>
	/// Vector used with indexing to turn number values of ranks into words (11 = Jack, 5 = 5 etc.).
	/// </summary>
	static std::vector<std::string> cardNames;

	/// <summary>
	/// Vector used with indexing to turn number values of suits into words (1 = Hearts, 3 = Clubs etc.).
	/// </summary>
	static std::vector<std::string> suitNames;

	/// <summary>
	/// Variable to store the spritesheet (res/img/sprite_sheet.png).
	/// </summary>
	static sf::Texture spritesheet;

	/// <summary>
	/// Variable to store the font (res/txt/PublicPixel.otf).
	/// </summary>
	static sf::Font font;

	/// <summary>
	/// Sprite for the card description bar for cards on the board.
	/// </summary>
	static sf::Sprite cardDescBar;

	static sf::Sprite cardEnergyBar;

	/// <summary>
	/// Sprite of the heart icon for use with cardDescBar.
	/// </summary>
	static sf::Sprite heart;

	/// <summary>
	/// Sprite of the club icon for use with cardDescBar.
	/// </summary>
	static sf::Sprite club;

	/// <summary>
	/// Width (in px) of a card tile (not including cardDescBarWidth) (currently 33).
	/// </summary>
	static float tileWidth;

	/// <summary>
	/// Height (in px) of a card tile (currently 45).
	/// </summary>
	static float tileHeight;

	/// <summary>
	/// Width (in px) of the cardDescBar (currently 16).
	/// </summary>
	static float cardDescBarWidth;

	/// <summary>
	/// Height (in px) of the health bars at the top an bottom (currently 20).
	/// </summary>
	static float healthBarHeight;

	/// <summary>
	/// Width (in px) of the whole window, which is 15 tiles wide (currently (tileWidth + cardDescBarWidth) * 15).
	/// </summary>
	static int windowWidth;

	/// <summary>
	/// Height (in px) of the whole window, which is 6 tiles wide (currently (tileHeight * 6) + (healthBarHeight * 2).
	/// </summary>
	static int windowHeight;

	// Important to track for special card effects
	static int turnNumber;
};