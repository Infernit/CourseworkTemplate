#include "card.h"
#include <iostream>

//________________________________//
//          CONSTRUCTORS          //
//________________________________//
//Default Constructor
Card::Card() : _cardRank(0), _isRoyal(false) {};

//Constructor for Suit and Rank
//--Sets effects and effect strength based off Suit and Rank if rank is >= 1 && <= 10
//--Declares card as royalty if rank is >= 11 && <= 13
//--Declares card as invalid if rank is <= 0 && >= 14
//--Not sure how ace handling will work yet
Card::Card(Suit suit, int rank)
	: _cardSuit(suit), _cardRank(rank), _cardEffects({}), _isRoyal(false)
{
	//Numbered cards
	if (rank >= 1 && rank <= 10) {
		int size = suit.getSuitEffects().size();
		std::vector<Effect> array(size);

		//Loops over each effect of the suit and adds it to the card, multiplied by the rank of the card
		for (int i = 0; i < size; i++) {
			array[i] = Effect(suit.getSuitEffects()[i].getIsPositiveEffect(),
				suit.getSuitEffects()[i].getEffectType(),
				suit.getSuitEffects()[i].getValue() * rank);
		}

		_cardEffects = array;

		//Set a max health and set health to max health based on suit and rank
		if (suit.getSuitName() == clubs) {
			_maxHealth = rank * 2;
		}
		else if (suit.getSuitName() == hearts) {
			_maxHealth = rank;
		}
		else {
			_maxHealth = 0;
		}
		
		_health = _maxHealth;
	}

	//Royalty
	else if (rank >= 11 && rank <= 13) {
		_isRoyal = true;
		//Will need a way to figure out royalty effects in here
	}

	//Invalid Cards
	else {
		std::cout << "Invalid Card Rank" << std::endl;
	}
	
}

//___________________________//
//          METHODS          //
//___________________________//
//Reduces the health of the card
//Returns true if card died, false if lived
bool Card::reduceHealth(int value) {
	_health -= value;

	if (_health <= 0) {
		//Card Dies
		return true;
	}

	return false;
}

void Card::increaseHealth(int value) {
	_health += value;

	if (_health > _maxHealth) {
		_health = _maxHealth;
	}
}

void Card::increaseEffect(int value, EffectType type) {
	int size = _cardEffects.size();

	for (int i = 0; i < size; i++) {
		if (_cardEffects[i].getEffectType() == type) {
			_effectIncrease += value;
		}
	}
}

bool Card::applyEffect(Effect effect) {
	switch (effect.getEffectType()) {
	case damage:
		reduceHealth(effect.getValue());
		break;

	case healing:
		increaseHealth(effect.getValue());
		break;

	case damageIncrease:
		increaseEffect(effect.getValue(), damage);
		break;

	case healingIncrease:
		increaseEffect(effect.getValue(), healing);
		break;

	case damageDecreasePercent:
		//damage decrease percent method
		break;

	case damageResist:
		//damage resist method
		break;

	default:
		std::cout << "No effect applied" << std::endl;
		break;
	}

	return true;
}

//Applies the effect of the card to a damagable (card or player)
void Card::applyCardEffect(Effectable* target) {
	int size = _cardEffects.size();

	for (int i = 0; i < size; i++) {
		_cardEffects[i].applyEffect(target);
	}
}

//____________________________//
//          GETTTERS          //
//____________________________//
//Returns the rank of the card
int Card::getCardRank() {
	return _cardRank;
}

int Card::getCardHealth() {
	return _health;
}

//Returns whether the card is royalty
bool Card::getIsRoyal() {
	return _isRoyal;
}

//Returns a vector of all card Effects 
std::vector<Effect> Card::getCardEffects() {
	return _cardEffects;
}

//Returns the suit of the card
Suit Card::getCardSuit() {
	return _cardSuit;
}



//____________________________//
//          TOSTRING          //
//____________________________//
// To string for the class for test printing
std::string Card::toString() {
	std::string effectsString = "";
	for (Effect effect : _cardEffects) {
		effectsString += effect.toString() + ", ";
	}
	return "Card Rank: " + std::to_string(_cardRank)
		+ ", Card Suit: [" + _cardSuit.toString()
		+ "], Card Royalty: " + std::to_string(_isRoyal)
		+ ", Card Effects: [" + effectsString + "]";
}