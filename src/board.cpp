#include "board.h"
#include <SFML/Graphics.hpp>
// For cerr
#include <iostream>
// Sprites
sf::Texture spritesheet;
sf::Sprite cards;

// Check if the spritesheet exists
void Board::init() {
	// Use string(RESOURCE_DIR) to get the resource directory path across multiple computers (?) without needing to copy sprite_sheet.png as path
    std::string sprite_path = std::string(RESOURCE_DIR) + "/img/sprite_sheet.png";
	std::cout << "Loading spritesheet from: " << sprite_path << std::endl; 

    if (!spritesheet.loadFromFile(sprite_path)) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    cards.setTexture(spritesheet);
    // Trial and error to cut it....
    // 306 width / 9, 276 height / 6
    cards.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(34, 46)));
}

Board::Board() {
    init();
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(cards);
        window.display();
    }

}