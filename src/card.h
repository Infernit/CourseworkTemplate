#pragma once
#include "suit.h"
#include "effectable.h"
#include <vector>

class Card : Effectable {

public:
//________________________________//
//          CONSTRUCTORS          //
//________________________________//
	Card();
	Card(Suit suit, int rank);

//___________________________//
//          METHODS          //
//___________________________//
	bool reduceHealth(int value) override;
	void applyCardEffect(Effectable* target);

//____________________________//
//          GETTTERS          //
//____________________________//
	int getCardRank();
	int getCardHealth();
	bool getIsRoyal();

	Suit getCardSuit();
	std::vector<Effect> getCardEffects();

//____________________________//
//          TOSTRING          //
//____________________________//
	std::string toString();

protected:
//___________________________________//
//          LOCAL VARIABLES          //
//___________________________________//
	int _cardRank;
	bool _isRoyal;

	Suit _cardSuit;
	std::vector<Effect> _cardEffects;
	
};
