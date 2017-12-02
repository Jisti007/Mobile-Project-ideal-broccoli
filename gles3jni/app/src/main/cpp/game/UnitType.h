#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Sprite.h"
#include "MapObject.h"

class Effect {
public:
	virtual void apply(MapObject* target) = 0;
};

class HPModification : public Effect {
public:
	HPModification(int amount);

	virtual void apply(MapObject* target);

private:
	int amount;
};

enum Target {
	enemy,
	friendly,
	unit,
	hex
};

class Skill {
public:
	Skill(Sprite* sprite, Target target, int range, float cost, std::vector<Effect*> effects);

	inline const Sprite* getSprite() const { return sprite; }
	inline const Target getTarget() const { return target; }
	inline const int getRange() const { return range; }
	inline const float getCost() const { return cost; }
	inline const std::vector<Effect*>& getEffects() const {  return effects; }

private:
	Sprite* sprite;
	Target target;
	int range;
	float cost;
	std::vector<Effect*> effects;
};

class UnitType {
public:
	UnitType(Sprite* sprite, int hp, int attack, int defense, int range, int movement);

	inline Sprite* getSprite() const { return sprite; }
	inline int getHP() { return hp; }
	inline int getAttack() { return attack; }
	inline int getDefense() { return defense; }
	inline const int getRange() const { return range; }
	inline const int getMovement() const { return movement; }

private:
	Sprite* sprite;
	int hp, attack, defense, range, movement;
};

#endif //GLES3JNI_UNITTYPE_H
