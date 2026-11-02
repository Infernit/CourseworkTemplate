#include "game_parameters.h"
#include "player.h"
#include "game_system.h"
#include "deck.h"
#include "card.h"
#include "testing.h"
#include <iostream>

int main()
{
	// Start to break off tests in main to keep everything tidy
	Testing::kill_player();
	Testing::test_deck_attributes();
	Testing::develop_effect_testing();
}
