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

    /* starting from fifth tile on first row, and last row */
    sf::Sprite cardTest1(spritesheet);

    // cut it
    
    cardTest1.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(tileWidth, tileHeight)));

    cardTest1.setPosition(sf::Vector2f(
        0,
        0
    ));

    Board::cards.push_back(cardTest1);
    
    // Test multiple cards later

}

Board::Board() {
    //init();
    // get window to obey width and height constants
    sf::RenderWindow window(sf::VideoMode({ windowWidth, windowHeight }), "SFML works!");

    // Practical legacy
 
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);

    init();
    
    while (window.isOpen()) {
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

        // card sprite logic
        // It is drawing a white box... Not card...
        for (sf::Sprite card : Board::cards) {
            // Card will be obvious against green background
            window.draw(card);
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
        }
        // problem line
        //window.clear();
  
        // display Board::cards later
        //window.draw(Board::cards);

        window.display();
        
    }

}