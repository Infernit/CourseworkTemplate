#include "game_parameters.h"
#include "player.h"
#include "game_system.h"
#include "deck.h"
#include "card.h"
#include "testing.h"
#include "board.h"
#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	GameSystem system;
	system.init();

	sf::RenderWindow window(
		sf::VideoMode({ (unsigned)GameParameters::windowWidth,
		(unsigned)GameParameters::windowHeight }),
		"Cabard");

	system.render(window);
	window.display();

	while (window.isOpen()) {
		system.update(0.f, window);
	}

	// Start to break off tests in main to keep everything tidy
	/*
	Testing::mockup_round();
	Testing::kill_player();
	Testing::test_deck_attributes();
	Testing::develop_effect_testing();
	Testing::fill_player_hand();
	Testing::testing_effects_stuff();
	*/
}
