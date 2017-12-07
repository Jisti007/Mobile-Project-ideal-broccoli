#ifndef GLES3JNI_UNITTYPE_H
#define GLES3JNI_UNITTYPE_H

#include "Skill.h"

class UnitType {
public:
	typedef std::vector<std::unique_ptr<Skill>> SkillList;

	UnitType(
		Sprite* sprite, std::string name, int hp, int defense, int movement, SkillList& skills
	);

	const std::vector<Skill*> getValidSkills(MapObject* user, MapObject* target) const;
	int getMaxSkillRange() const;

	inline Sprite* getSprite() const { return sprite; }
	inline const int getHP() const { return hp; }
	inline const std::string getName() const { return name; };
	inline const int getDefense() const { return defense; }
	inline const int getMovement() const { return movement; }
	inline const SkillList& getSkills() const { return skills; };

private:
	Sprite* sprite;
	int hp, defense, movement;
	SkillList skills;
	std::string name;
};

#endif //GLES3JNI_UNITTYPE_H
