#include "board.h"
#include <SFML/Graphics.hpp>
// For cerr
#include <iostream>
// Sprites
sf::Texture spritesheet;
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
sf::Sprite cardTest1(spritesheet);

// Check if the spritesheet exists
void Board::init() {

    // Put sprites on tiles (?)
    // Put somewhere else (console spam) later. Keep now for testing

    // Use string(RESOURCE_DIR) to get the resource directory path across multiple computers (?) without needing to copy sprite_sheet.png as path
    std::string sprite_path = std::string(RESOURCE_DIR) + "/img/sprite_sheet.png";
    std::cout << "Loading spritesheet from: " << sprite_path << std::endl;

    if (!spritesheet.loadFromFile(sprite_path)) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }

    // Make individual chards accessible from this
    //sf::Texture spritesheet;

    // cut it
    
    cardTest1.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(tileWidth, tileHeight)));

    // Set new position to current grid position using mouse

    /*
    cardTest1.setPosition(sf::Vector2f(
        0,
        0
    ));
    */

    Board::cards.push_back(cardTest1);
    
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

Board::Board() {
    //init();
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

        // problem line
        //window.clear();
  
        // display Board::cards later
        //window.draw(Board::cards);

        window.draw(cardTest1);
        window.display();
        
    }

}
