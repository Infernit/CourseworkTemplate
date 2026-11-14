#include "card.h"
#include <iostream>

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
	
};

//Returns a vector of all card Effects 
std::vector<Effect> Card::getCardEffects() {
	return _cardEffects;
}

//Returns the suit of the card
Suit Card::getCardSuit() {
	return _cardSuit;
}

//Returns the rank of the card
int Card::getCardRank() {
	return _cardRank;
}

//Returns whether the card is royalty
bool Card::getIsRoyal() {
	return _isRoyal;
}

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