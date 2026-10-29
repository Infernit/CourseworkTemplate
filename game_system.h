#pragma once
#include "game_parameters.h"

struct GameSystem {
	static void init();
	static void reset();
	static void clean();
	static void update(const float& dt);
	static void render();
};