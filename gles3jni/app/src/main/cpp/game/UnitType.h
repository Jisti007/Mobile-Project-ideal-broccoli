#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Sprite.h"

class UnitType {
public:
	UnitType(Sprite* sprite, int hp, int attack, int defense, int range);
	~UnitType();

	inline Sprite* getSprite() const { return sprite; }
	inline int getHP() { return hp; }
	inline int getAttack() { return attack; }
	inline int getDefense() { return defense; }
	inline const int getRange() const { return range; }

private:
	Sprite* sprite;
	int hp, attack, defense, range;
};

#endif //GLES3JNI_UNITTYPE_H
