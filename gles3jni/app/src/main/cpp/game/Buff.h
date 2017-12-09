#ifndef GLES3JNI_BUFF_H
#define GLES3JNI_BUFF_H

#include <memory>
#include <vector>
#include "Sprite.h"
#include "Skill.h"

class BuffEffect {
public:
	virtual int getDamageModifierAgainst(Damage* damage) { return 0; }
};

class Resistance : public BuffEffect {
public:
	Resistance(DamageType* type, int amount);

	virtual int getDamageModifierAgainst(Damage* damage);

private:
	DamageType* type;
	int amount;

};

class Buff {
public:
	typedef std::vector<std::unique_ptr<BuffEffect>> EffectList;

	Buff(EffectList& effects, const char* name, Sprite* sprite);

	virtual int getDamageModifierAgainst(Damage* damage);

	inline const std::string getName() const { return name; }
	inline const Sprite* getSprite() const { return sprite; }

private:
	EffectList effects;
	std::string name;
	Sprite* sprite;
};

#endif //GLES3JNI_BUFF_H
