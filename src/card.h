#pragma once
#include "suit.h"
#include "effectable.h"
#include <vector>
#include <map>

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
	void increaseEffect(int value);
	void reduceIncreaseEffect(int value);
	void setDamageDecreasePercent(float percent);
	bool applyEffect(Effect effect) override;
	bool applyCardEffect(Effectable* target);
	void resetDamageDecrease();

//____________________________//
//          GETTTERS          //
//____________________________//
	int getCardRank();
	int getCardHealth();
	int getCardMaxHealth();
	bool getIsRoyal();

	Suit getCardSuit();
	int getEffectIncreases();
	Effect getCardEffect();

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
	std::vector<float> _damageDecreases;
	int _effectIncrease;
	Effect _cardEffect;
	
};
