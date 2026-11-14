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
	// Start to break off tests in main to keep everything tidy
	Testing::kill_player();
	Testing::test_deck_attributes();
	Testing::develop_effect_testing();
	Testing::fill_player_hand();
	Testing::testing_effects_stuff();
	//Board();
}
