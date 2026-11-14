#pragma once
#include "suit.h"
#include "effectable.h"
#include <vector>

class Card : public Effectable {

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
	void increaseHealth(int value) override;
	void increaseEffect(int value, EffectType type);
	bool applyEffect(Effect effect) override;
	void applyCardEffect(Effectable* target);

//____________________________//
//          GETTTERS          //
//____________________________//
	int getCardRank();
	int getCardHealth();
	int getCardMaxHealth();
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
	int _effectIncrease;
	bool _isRoyal;

	Suit _cardSuit;
	std::vector<Effect> _cardEffects;
	
};
