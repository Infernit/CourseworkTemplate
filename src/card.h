#pragma once
#include "suit.h"
#include "effectable.h"
#include <vector>
#include <map>
// for jack club damage
#include <random>

class Card : public Effectable {

public:
//________________________________//
//          CONSTRUCTORS          //
//________________________________//
	
	/// <summary>
	/// Default constructor.
	/// </summary>
	Card();

	/// <summary>
	/// Constructor using suit and rank.
	/// </summary>
	/// <param name="suit">Suit of card.</param>
	/// <param name="rank">Rank of card.</param>
	Card(Suit suit, int rank);

//___________________________//
//          METHODS          //
//___________________________//
	
	/// <summary>
	/// Reduces the health of the card by the value.
	/// </summary>
	/// <param name="value">Value to reduce the health by.</param>
	/// <returns>Returns true if the card died, false otherwise.</returns>
	bool reduceHealth(int value) override;

	/// <summary>
	/// Increases the health of the card by the value.
	/// </summary>
	/// <param name="value">Value to increase the health by.</param>
	void increaseHealth(int value) override;

	/// <summary>
	/// Increases the value of the effectIncrease by the value.
	/// </summary>
	/// <param name="value">Value to increase the effectIncrease by.</param>
	void increaseEffect(int value);

	/// <summary>
	/// Reduces the value of effectIncrease by the value.
	/// </summary>
	/// <param name="value">Value to reduce the effectIncrease by.</param>
	void reduceIncreaseEffect(int value);

	/// <summary>
	/// Sets the percent of damage decrease based on the current damage decrease.
	/// </summary>
	/// <param name="percent">Percent to reduce by.</param>
	void setDamageDecreasePercent(float percent);

	/// <summary>
	/// Resets the damage decrease percent back to 0 (1x damage).
	/// </summary>
	void resetDamageDecrease();

	/// <summary>
	/// Applies the referenced effect to this card.
	/// </summary>
	/// <param name="effect">Effect to apply</param>
	/// <returns>True if effect applied, otherwise false.</returns>
	bool applyEffect(Effect effect) override;

	/// <summary>
	/// Applies the effect of this card to the target.
	/// </summary>
	/// <param name="target">Target to apply effect to.</param>
	/// <returns>True if effect applied, otherwise false.</returns>
	bool applyCardEffect(Effectable* target);
	
	/// <summary>
	/// Sets isUsable based on value.
	/// </summary>
	/// <param name="value">Value to set to.</param>
	void setIsUsable(bool value);

	int generateJackDamage();

//____________________________//
//          GETTTERS          //
//____________________________//
	int getCardRank();
	int getCardHealth();
	int getCardMaxHealth();
	bool getIsRoyal();
	bool getIsUsable();
	bool getIsDead();

	Suit getCardSuit();
	int getEffectIncreases();
	float getDamageDecrease();
	Effect getCardEffect();

	// Setters
	void setCardEnergyCost(int energyCost);


//____________________________//
//          TOSTRING          //
//____________________________//
	std::string toString();

protected:
//___________________________________//
//          LOCAL VARIABLES          //
//___________________________________//
	
	/// <summary>
	/// Number rank of the card (11 - 13 are Royals).
	/// </summary>
	int _cardRank;

	// Rank of ace stays as 1 as 11 is jack, so this must be a separate property
	int _cardEnergyCost;

	/// <summary>
	/// Determines if the card is a royal.
	/// </summary>
	bool _isRoyal;

	/// <summary>
	/// Determines if the card can be used.
	/// </summary>
	bool _isUsable;

	/// <summary>
	/// Determines if the card is dead.
	/// </summary>
	bool _isDead;

	/// <summary>
	/// The suit of the card.
	/// </summary>
	Suit _cardSuit;

	/// <summary>
	/// Vector of damage decrease percentages applied.
	/// </summary>
	std::vector<float> _damageDecreases;

	/// <summary>
	/// The value of the diamond buff applied to the card.
	/// </summary>
	int _effectIncrease;

	/// <summary>
	/// The effect that the card applies.
	/// </summary>
	Effect _cardEffect;
	
};
