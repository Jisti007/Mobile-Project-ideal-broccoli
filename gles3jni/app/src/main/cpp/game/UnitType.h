#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Sprite.h"
#include "MapObject.h"

class Effect {
public:
	virtual void apply(MapObject* user, MapObject* target) = 0;
	/// Helps the AI evaluate the value of an action that will have this effect.
	/// The higher the returned number, the better for the AI.
	virtual float evaluate(MapObject* user, MapObject* target) = 0;
};

class HPModification : public Effect {
public:
	HPModification(int amount);

	virtual void apply(MapObject* user, MapObject* target);
	virtual float evaluate(MapObject* user, MapObject* target);

private:
	int amount;
};

enum TargetType {
	enemy,
	friendly,
	unit,
	hex
};

class Skill {
public:
	typedef std::vector<std::unique_ptr<Effect>> EffectList;

	Skill(
		Sprite* sprite, TargetType targetType, int range, float cost, EffectList& effects
	);

	/// Helps the AI evaluate the value of using this skill.
	/// The higher the returned number, the better for the AI.
	float evaluate(MapObject* user, MapObject* target);
	/// Returns true if the rules allow the user to use this skill against the target.
	bool validate(MapObject* user, MapObject* target);

	inline Sprite* getSprite() const { return sprite; }
	inline const TargetType getTargetType() const { return targetType; }
	inline const int getRange() const { return range; }
	inline const float getCost() const { return cost; }
	inline const EffectList& getEffects() const {  return effects; }

private:
	Sprite* sprite;
	TargetType targetType;
	int range;
	float cost;
	EffectList effects;
};

class UnitType {
public:
	typedef std::vector<std::unique_ptr<Skill>> SkillList;

	UnitType(
		Sprite* sprite, int hp, int attack, int defense,
		int range, int movement, SkillList& skills
	);

	const std::vector<Skill*> getValidSkills(MapObject* user, MapObject* target) const;

	inline Sprite* getSprite() const { return sprite; }
	inline int getHP() { return hp; }
	inline int getAttack() { return attack; }
	inline int getDefense() { return defense; }
	inline const int getRange() const { return range; }
	inline const int getMovement() const { return movement; }
	inline const SkillList& getSkills() { return skills; };

private:
	Sprite* sprite;
	int hp, attack, defense, range, movement;
	SkillList skills;
};

#endif //GLES3JNI_UNITTYPE_H
