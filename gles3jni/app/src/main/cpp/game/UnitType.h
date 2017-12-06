#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Skill.h"

class UnitType {
public:
	typedef std::vector<std::unique_ptr<Skill>> SkillList;

	UnitType(
		Sprite* sprite, int hp, int defense, int movement, SkillList& skills
	);

	const std::vector<Skill*> getValidSkills(MapObject* user, MapObject* target) const;
	int getMaxSkillRange() const;

	inline Sprite* getSprite() const { return sprite; }
	inline int getHP() { return hp; }
	inline int getDefense() { return defense; }
	inline const int getMovement() const { return movement; }
	inline const SkillList& getSkills() const { return skills; };

private:
	Sprite* sprite;
	int hp, defense, movement;
	SkillList skills;
};

#endif //GLES3JNI_UNITTYPE_H
