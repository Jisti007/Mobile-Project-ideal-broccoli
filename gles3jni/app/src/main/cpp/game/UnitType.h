#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Skill.h"

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
