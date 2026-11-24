#include "card.h"
#include <iostream>

//________________________________//
//          CONSTRUCTORS          //
//________________________________//

Card::Card() 
	: _cardRank(0), 
	_cardEnergyCost(0),
	_isRoyal(false), 
	// Use for capturing logic. Trap: card auto sets to usable again next turn???
	_isUsable(false),
	_isDead(false),
	// Is a usable card auto set to dead ???
	//_isCaptured(false),
	_effectIncrease(0) {};

Card::Card(Suit suit, int rank)
	: _cardSuit(suit),
	_cardEnergyCost(0),
	_cardRank(rank),
	_cardEffect({}),
	_isRoyal(false),
	_isUsable(false),
	_isDead(false),
	_effectIncrease(0) {

		//All cards
		// NO CODE YET, WILL BE SOME STUFF

		//Numbered cards
		if (rank >= 1 && rank <= 10) {
			_cardEffect = Effect(suit.getSuitEffect().getIsPositiveEffect(),
				suit.getSuitEffect().getEffectType(),
				suit.getSuitEffect().getValue() * rank);

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
			
			int damage_val = 0;
			_isRoyal = true;
			_cardEnergyCost = 10;

			// Rank and suit are the determining factors for what it does
			switch(suit.getSuitName()) {
				case hearts:
					switch (rank) {
						//Jack of hearts
						case 11:
							_cardEffect = Effect(true, cleanse, 0);
							break;
						}
						break;

				// Club royals
				case clubs:
					switch (rank) {
						// Jack of Clubs
						case 11:
							// Jack - Randomly deals between 5 and 20 damage.
							// Set it to a random int between 5 and 20
							// Function so its damage can be changed per turn
							damage_val = Card::generateJackDamage();

							_cardEffect = Effect(false, damage, damage_val);
							break;

						// Queen of Clubs
						case 12:
							// Queen - Damage dealt is spread evenly across all enemy minions.
							// ??????
							break;

						// King of Clubs
						case 13:
							// King - Has 40 health instead of 20. Deals 5 damage instead of 10.
							_health = 40;
							_cardEffect = Effect(false, damage, 5);
							break;
						}

					break;

				// ALIGATOR
				// Property of effect: Spread

				// Queen clubs damages all played cards, 
				// Jack spades doubles all energy cost of hand cards,
				// Queen spades halves all enemy damage of played cards,
				// Jack diamonds halves energy cost of player hand cards,
				// King diamonds grants all played cards 10 extra health,
				// Jack hearts removes all debuffs from played cards

				//* Heart Ace heals all played cards by 5 every turn present
				
				// Graveyard

				// Queen hearts brings back next numbered card once every 3 turns until dead
				// Queen diamond brings back one non ace then perishes

				// ?????
		
				// King sucks all damage until dead
				//* Ace clubs captures and deals 11 damage until capatured dies etc. 
					// Property Captured ^^^
				// King spades skips turn


				// Heart royals
			}
			//Will need a way to figure out royalty effects in here
		}

		//Invalid Cards
		else {
			std::cout << "Invalid Card Rank" << std::endl;
		}
	
	} // constructor end


//___________________________//
//          METHODS          //
//___________________________//
//Reduces the health of the card
//Returns true if card died, false if lived
bool Card::reduceHealth(int value) {
	_health -= value;

	if (_health <= 0) {
		_isDead = true;
	}

	return _isDead;
}

//Increases the health of the card
//Cannot go higher than max health
void Card::increaseHealth(int value) {
	_health += value;

	if (_health > _maxHealth) {
		_health = _maxHealth;
	}
}

//Increases the effect type by value in effect increase
void Card::increaseEffect(int value) {
	_effectIncrease += value;
}

void Card::reduceIncreaseEffect(int value) {
	int temp = _effectIncrease;
	if (temp - value < 0) {
		_effectIncrease = 0;
	}
	else {
		_effectIncrease -= value;
	}
}

//Sets the damage decrease percentage
void Card::setDamageDecreasePercent(float percent) {
	_damageDecreases.push_back(percent);
}

// PINEAPPLE
bool Card::applyEffect(Effect effect) {
	switch (effect.getEffectType()) {
	case damage:
		//If card has damage resist
		if (_effectIncrease != 0) {
			int value = _effectIncrease - effect.getValue();

			//If damage resist is less than hit value, apply some to actual health and reduce resist to 0
			if (value < 0) {
				// Jack???
				reduceHealth(effect.getValue() - _effectIncrease);
				reduceIncreaseEffect(_effectIncrease);
			}
			//Otherwise just take it from damage resist
			else {
				reduceIncreaseEffect(effect.getValue());
			}
		}
		//If card does not have damage resist
		else {
			reduceHealth(effect.getValue());
		}
		break;

	case healing:
		increaseHealth(effect.getValue());
		break;

	case diamondEffect:
		increaseEffect(effect.getValue());
		break;

	case damageDecreasePercent:
		setDamageDecreasePercent(effect.getValue());
		break;

	case cleanse:
		resetDamageDecrease();

	default:
		std::cout << "No effect applied" << std::endl;
		return false;
		break;
	}

	return true;
}

//Applies the effect of the card to a damagable (card or player)
bool Card::applyCardEffect(Effectable* target) {

	if (_cardEffect.getEffectType() == damage || _cardEffect.getEffectType() == healing) {

		float value = _cardEffect.getValue();

		value += _effectIncrease;

		_effectIncrease = 0;

		value *= getDamageDecrease();

		Effect damageEffect(false, _cardEffect.getEffectType(), value);

		if (damageEffect.applyEffect(target)) {
			_isUsable = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (_cardEffect.applyEffect(target)) {
			_isUsable = false;
			return true;
		}
		else {
			return false;
		}
	}
		
	
}

void Card::resetDamageDecrease() {
	_damageDecreases = {};
}

void Card::setIsUsable(bool value) {
	_isUsable = value;
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

int Card::getCardMaxHealth() {
	return _maxHealth;
}

//Returns whether the card is royalty
bool Card::getIsRoyal() {
	return _isRoyal;
}

bool Card::getIsUsable() {
	return _isUsable;
}

bool Card::getIsDead() {
	return _isDead;
}

int Card::getEffectIncreases() {
	return _effectIncrease;
}

float Card::getDamageDecrease() {
	float value = 1;

	for (int j = 0; j < _damageDecreases.size(); j++) {
		value -= value * _damageDecreases[j];
	}

	return value;
}

//Returns a vector of all card Effects 
Effect Card::getCardEffect() {
	return _cardEffect;
}

//Returns the suit of the card
Suit Card::getCardSuit() {
	return _cardSuit;
}

int Card::getCardEnergyCost() {
	return _cardEnergyCost;
}

// Setter
void Card::setCardEnergyCost(int energyCost) {
	_cardEnergyCost = energyCost;
}

// Helper
void Card::generateJackDamage() {
	std::random_device random;
	std::mt19937 rng(random());
	std::uniform_int_distribution<> dis(5, 20);

	_cardEffect = Effect(false, damage, dis(rng));
}

//____________________________//
//          TOSTRING          //
//____________________________//
// To string for the class for test printing
std::string Card::toString() {
	return "Card Rank: " + std::to_string(_cardRank)
		+ ", Card Suit: [" + _cardSuit.toString()
		+ "], Card Royalty: " + std::to_string(_isRoyal)
		+ ", Card Effects: " + _cardEffect.toString();
}