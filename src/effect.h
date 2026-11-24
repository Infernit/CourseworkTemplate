#pragma once
#include <string>

class Effectable;

enum EffectType {
	none,
	damage,
	healing,
	diamondEffect,
	damageDecreasePercent,
	// Hearts Jack - Cleanses all friendly cards (removes any debuffs).
	cleanse,
	// Hearts Queen - Bring back the next numbered card from the graveyard once every 3 turns whilst this card is on the board.
	// Diamonds Queen - Bring back one non - ace from graveyard(then Queen disappears).
	graveyard,
	// Hearts King - Cannot heal or be healed.All damage dealt to any friendly card is dealt to this card instead.Has 100 health.
	heartsKing,
	// Hearts 11 Ace - Heal all friendly minions by 5 every turn while on the board.
	healAll,
	// Diamond Jack - Halves energy cost of all other cards currently in hand.
	// Diamonds 11 Ace - Fully restore energy plus gain an extra 11.
	// Spades Jack - Doubles mana cost of all cards in the opponent’s hand(to a cap of their max mana).
	mana,
	// Diamonds King - Rally effect.Grant all cards on board 10 overhealth.
	overhealth,
	// Clubs Queen - Damage dealt is spread evenly across all enemy minions.
	damageAll,
	// Spades Queen - Halves all enemy damage dealt by enemies for 2 turns.
	debuffDamageAll,
	// Clubs 11 Ace - Captures an enemy minion. The captured cannot do any action, and takes 11 damage every turn until they die. Can only be freed by cleanse or capturing/killing. Once the captured card dies, the ace can capture another card. The captured does not start taking damage until the turn after the capture.
	capture,
	// Spades King - Skips the opponent’s next turn.
	skipTurn,
	// Spades 11 Ace - Instakills anything it is applied to.
	// Just set it to 101 damage
};

class Effect {

public:
	Effect();
	Effect(bool isPositive, EffectType type, float value);
	bool applyEffect(Effectable* damagable);
	bool getIsPositiveEffect();
	bool getIsSpreadableEffect();
	EffectType getEffectType();
	float getValue();
	std::string toString();
	// Property of effect: Spread

	// Queen clubs damages all played cards, 
	// Jack spades doubles all energy cost of hand cards,
	// Queen spades halves all enemy damage of played cards,
	// Jack diamonds halves energy cost of player hand cards,
	// King diamonds grants all played cards 10 extra health,
	// Jack hearts removes all debuffs from played cards

	//* Heart Ace heals all played cards by 5 every turn present
	bool spreadable;
	bool gravyardInteractable;

protected:
	

private:
	bool isPositive; //H: True, D: True, C: False, S: False
	EffectType effectType;
	float value;

	// Maybe change this system to have an enum declaring the type and then a value, apply multiple effects rather than one for diamonds.
	// So just have positiveEffect, enum and value (which will be a float) 

	// Diamonds will provide all buffs when applied, but be removed as soon as one is used.
	// For the effects in the suit classes, set all values to lowest, then when effect is added to the card times by rank.

};